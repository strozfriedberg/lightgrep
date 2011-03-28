#include "instructions.h"

#include "program.h"

#include <stdexcept>
#include <iomanip>

template<typename IntT>
class HexCode {
public:
  HexCode(IntT i): MyI(i) {}

  IntT MyI;
};

std::ostream& operator<<(std::ostream& out, const HexCode<byte>& hex) {
  out << std::hex << std::setfill('0') << std::setw(2) << (unsigned short)hex.MyI;
  return out;
}

std::ostream& operator<<(std::ostream& out, const HexCode<uint32>& hex) {
  out << std::hex << std::setfill('0') << std::setw(8) << hex.MyI;
  return out;
}

std::string Instruction::toString() const {
  std::string ret;
  std::stringstream buf;
  switch (OpCode) {
    case LIT_OP:
      buf << "Literal 0x" << HexCode<byte>(Op.Literal) << "/'" << Op.Literal << '\'';
      break;
    case EITHER_OP:
      buf << "Either 0x" << HexCode<byte>(Op.Range.First) << "/'" << Op.Range.First << "', 0x" << HexCode<byte>(Op.Range.Last) << "/'" << Op.Range.Last << '\'';
      break;
    case RANGE_OP:
      buf << "Range 0x" << HexCode<byte>(Op.Range.First) << "/'" << Op.Range.First << "'-0x" << HexCode<byte>(Op.Range.Last) << "/'" << Op.Range.Last << '\'';
      break;
    case ANY_OP:
      buf << "Any";
      break;
    case BIT_VECTOR_OP:
      buf << "BitVector";
      break;
    case JUMP_OP:
      buf << "Jump 0x" << HexCode<uint32>(*reinterpret_cast<const uint32*>(this+1)) << '/' << std::dec << (*reinterpret_cast<const uint32*>(this+1));
      break;
    case JUMP_TABLE_OP:
      buf << "JumpTable";
      break;
    case JUMP_TABLE_RANGE_OP:
      buf << "JmpTblRange 0x" << HexCode<byte>(Op.Range.First) << "/'" << Op.Range.First << "'-0x" << HexCode<byte>(Op.Range.Last) << "/'" << Op.Range.Last << '\'';
      break;
    case FORK_OP:
      buf << "Fork 0x" << HexCode<uint32>(*reinterpret_cast<const uint32*>(this+1)) << '/' << std::dec << (*reinterpret_cast<const uint32*>(this+1));
      break;
    case CHECK_HALT_OP:
      buf << "CheckHalt 0x" << HexCode<uint32>(Op.Offset) << '/' << std::dec << Op.Offset;
      break;
    case LABEL_OP:
      buf << "Label " << Op.Offset;
      break;
    case MATCH_OP:
      buf << "Match";
      break;
    case HALT_OP:
      buf << "Halt";
      break;
    default:
      buf << "* UNRECOGNIZED *";
  };
  ret = buf.str();
  return ret;
}

Instruction Instruction::makeLit(byte b) {
  Instruction i;
  i.OpCode = LIT_OP;
  i.Op.Literal = b;
  return i;
}

Instruction Instruction::makeEither(byte one, byte two) {
  Instruction i;
  i.OpCode = EITHER_OP;
  i.Op.Range.First = one;
  i.Op.Range.Last = two;
  return i;
}

Instruction Instruction::makeRange(byte first, byte last) {
  if (last < first) {
    THROW_WITH_OUTPUT(std::range_error, "out-of-order range; first = " << first << "; last = " << last);
  }
  Instruction i;
  i.OpCode = RANGE_OP;
  i.Op.Range.First = first;
  i.Op.Range.Last = last;
  return i;
}

Instruction Instruction::makeAny() {
  Instruction i;
  i.OpCode = ANY_OP;
  i.Op.Offset = 0;
  return i;
}

Instruction Instruction::makeBitVector() {
  Instruction i;
  i.OpCode = BIT_VECTOR_OP;
  return i;
}

Instruction Instruction::makeJump(Instruction* ptr, uint32 offset) {
  // "24 bits ought to be enough for anybody." --Jon Stewart
  // I once implemented a 24-bit VM in Java for a class; that sucked ass -- JLS
  Instruction i;
  i.OpCode = JUMP_OP;
  i.Op.Offset = 0;
  *reinterpret_cast<uint32*>(ptr+1) = offset;
  return i;
}

Instruction Instruction::makeJumpTable() {
  Instruction i;
  i.OpCode = JUMP_TABLE_OP;
  i.Op.Offset = 0;
  return i;
}

Instruction Instruction::makeJumpTableRange(byte first, byte last) {
  Instruction i = makeRange(first, last);
  i.OpCode = JUMP_TABLE_RANGE_OP;
  return i;
}

Instruction Instruction::makeRaw24(uint32 val) {
  if (val >= (1 << 24)) {
    THROW_WITH_OUTPUT(
      std::overflow_error,
      "raw values are 24 bit; specified value was " << val
    );
  }

  Instruction i;
  i.Op.Offset = val;
  return i;
}

Instruction Instruction::makeLabel(uint32 label) {
  Instruction i = makeRaw24(label);
  i.OpCode = LABEL_OP;
  return i;
}

Instruction Instruction::makeMatch() {
  Instruction i = makeRaw24(0);
  i.OpCode = MATCH_OP;
  return i;
}

Instruction Instruction::makeFork(Instruction* ptr, uint32 offset) {
  Instruction i = makeJump(ptr, offset);
  i.OpCode = FORK_OP;
  return i;
}

Instruction Instruction::makeCheckHalt(uint32 checkIndex) {
  Instruction i = makeRaw24(checkIndex);
  i.OpCode = CHECK_HALT_OP;
  return i;
}

Instruction Instruction::makeHalt() {
  Instruction i;
  i.OpCode = HALT_OP;
  i.Op.Offset = 0;
  return i;
}

Instruction Instruction::makeRaw32(uint32 val) {
  Instruction i;
  *reinterpret_cast<uint32*>(&i) = val;
  return i;
}

std::ostream& operator<<(std::ostream& out, const Instruction& instr) {
  out << instr.toString();
  return out;
}

std::ostream& printIndex(std::ostream& out, uint32 i) {
  out << std::setfill('0') << std::setw(7) << i << '\t';
  return out;
}

std::ostream& operator<<(std::ostream& out, const Program& prog) {
  for (uint32 i = 0; i < prog.size(); ++i) {
    printIndex(out, i) << prog[i] << '\n';
    if (prog[i].OpCode == BIT_VECTOR_OP) {
      for (uint32 j = 1; j < 9; ++j) {
        out << std::dec << std::setfill('0') << std::setw(7) << i + j << '\t' << std::hex << std::setfill('0') << std::setw(8) << *(uint32*)(&prog[i]+j) << '\n';
      }
      out << std::dec;
      i += 8;
    }
    else if (prog[i].OpCode == JUMP_TABLE_OP || prog[i].OpCode == JUMP_TABLE_RANGE_OP) {
      uint32 start = 0,
             end = 255;
      if (prog[i].OpCode == JUMP_TABLE_RANGE_OP) {
        start = prog[i].Op.Range.First;
        end = prog[i].Op.Range.Last;
      }
      for (uint32 j = start; j <= end; ++j) {
        ++i;
        printIndex(out, i) << std::setfill(' ') << std::setw(3) << j << ": " << *reinterpret_cast<const uint32*>(&prog[i]) << '\n';
      }
    }
    else if (prog[i].OpCode == JUMP_OP || prog[i].OpCode == FORK_OP) {
      ++i;
      printIndex(out, i) << *reinterpret_cast<const uint32*>(&prog[i]) << '\n';
    }
  }
  return out;
}
