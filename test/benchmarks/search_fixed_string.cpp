#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../stest.h"

namespace {
	std::string holmes1(
R"(The road in which we found ourselves as we turned round the corner from the retired Saxe-Coburg Square presented as great a contrast to it as the front of a picture does to the back. It was one of the main arteries which conveyed the traffic of the City to the north and west. The roadway was blocked with the immense stream of commerce flowing in a double tide inward and outward, while the footpaths were black with the hurrying swarm of pedestrians. It was difficult to realise as we looked at the line of fine shops and stately business premises that they really abutted on the other side upon the faded and stagnant square which we had just quitted.

"Let me see," said Holmes, standing at the corner and glancing along the line, "I should like just to remember the order of the houses here. It is a hobby of mine to have an exact knowledge of London. There is Mortimer's, the tobacconist, the little newspaper shop, the Coburg branch of the City and Suburban Bank, the Vegetarian Restaurant, and McFarlane's carriage-building depot. That carries us right on to the other block. And now, Doctor, we've done our work, so it's time we had some play. A sandwich and a cup of coffee, and then off to violin-land, where all is sweetness and delicacy and harmony, and there are no red-headed clients to vex us with their conundrums."

My friend was an enthusiastic musician, being himself not only a very capable performer but a composer of no ordinary merit. All the afternoon he sat in the stalls wrapped in the most perfect happiness, gently waving his long, thin fingers in time to the music, while his gently smiling face and his languid, dreamy eyes were as unlike those of Holmes the sleuth-hound, Holmes the relentless, keen-witted, ready-handed criminal agent, as it was possible to conceive. In his singular character the dual nature alternately asserted itself, and his extreme exactness and astuteness represented, as I have often thought, the reaction against the poetic and contemplative mood which occasionally predominated in him. The swing of his nature took him from extreme languor to devouring energy; and, as I knew well, he was never so truly formidable as when, for days on end, he had been lounging in his armchair amid his improvisations and his black-letter editions. Then it was that the lust of the chase would suddenly come upon him, and that his brilliant reasoning power would rise to the level of intuition, until those who were unacquainted with his methods would look askance at him as on a man whose knowledge was not that of other mortals. When I saw him that afternoon so enwrapped in the music at St. James's Hall I felt that an evil time might be coming upon those whom he had set himself to hunt down.
)");

	std::string holmes2(
R"("My dear fellow," said Sherlock Holmes as we sat on either side of the fire in his lodgings at Baker Street, "life is infinitely stranger than anything which the mind of man could invent. We would not dare to conceive the things which are really mere commonplaces of existence. If we could fly out of that window hand in hand, hover over this great city, gently remove the roofs, and peep in at the queer things which are going on, the strange coincidences, the plannings, the cross-purposes, the wonderful chains of events, working through generations, and leading to the most outre results, it would make all fiction with its conventionalities and foreseen conclusions most stale and unprofitable."

"And yet I am not convinced of it," I answered. "The cases which come to light in the papers are, as a rule, bald enough, and vulgar enough. We have in our police reports realism pushed to its extreme limits, and yet the result is, it must be confessed, neither fascinating nor artistic."

"A certain selection and discretion must be used in producing a realistic effect," remarked Holmes. "This is wanting in the police report, where more stress is laid, perhaps, upon the platitudes of the magistrate than upon the details, which to an observer contain the vital essence of the whole matter. Depend upon it, there is nothing so unnatural as the commonplace."

I smiled and shook my head. "I can quite understand your thinking so." I said. "Of course, in your position of unofficial adviser and helper to everybody who is absolutely puzzled, throughout three continents, you are brought in contact with all that is strange and bizarre. But here"--I picked up the morning paper from the ground--"let us put it to a practical test. Here is the first heading upon which I come. 'A husband's cruelty to his wife.' There is half a column of print, but I know without reading it that it is all perfectly familiar to me. There is, of course, the other woman, the drink, the push, the blow, the bruise, the sympathetic sister or landlady. The crudest of writers could invent nothing more crude."

"Indeed, your example is an unfortunate one for your argument," said Holmes, taking the paper and glancing his eye down it. "This is the Dundas separation case, and, as it happens, I was engaged in clearing up some small points in connection with it. The husband was a teetotaler, there was no other woman, and the conduct complained of was that he had drifted into the habit of winding up every meal by taking out his false teeth and hurling them at his wife, which, you will allow, is not an action likely to occur to the imagination of the average story-teller. Take a pinch of snuff, Doctor, and acknowledge that I have scored over you in your example.\"
)");

	TEST_CASE("foo") {

		STest searcher("foo");

		BENCHMARK("hits short") {
			return searcher.search("This is a clear example of the foo going fubar.");
		};

		BENCHMARK("no hits short") {
			return searcher.search("This is another example of the baz going fubar.");
		};

		BENCHMARK("hits long") {
			return searcher.search(holmes1);
		};

		BENCHMARK("no hits long") {
			return searcher.search(holmes2);
		};
	}


	TEST_CASE("discretion") {
		STest searcher("discretion");

		BENCHMARK("hits long") {
			return searcher.search(holmes2);
		};

		BENCHMARK("no hits long") {
			return searcher.search(holmes1);
		};
	}
}
