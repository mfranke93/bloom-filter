#include <iostream>
#include <array>
#include <algorithm>
#include <string>

#include "../lib/bloom_filter"

struct S
{
    std::string s;
    int i;
};

// must provide a hash function
namespace std
{
    template<>
    struct hash<S>
    {
        using argument_type = S;
        using result_type = std::size_t;

        result_type
        operator()(argument_type const& arg) const noexcept
        {
            result_type s1 = std::hash<std::string>{}(arg.s);
            result_type s2 = std::hash<int>{}(arg.i);
            s1 ^= s2;
            return std::hash<result_type>{}(s1);
        }
    };
}

int main()
{
    constexpr size_t const num_hash_fns = 16;
    constexpr size_t const precision    = 7;

    std::array<S, 200> members =
    {{
         {"rayleigh", 12392 },
         {"campaign", -16758 },
         {"none", -10388 },
         {"ibilltes", 9002 },
         {"contraptions", -9980 },
         {"amphetamine", 1262 },
         {"twinkie", 12469 },
         {"henpeck", -5559 },
         {"ballerina's", -9097 },
         {"hallow", -3192 },
         {"traversal", 3319 },
         {"reappear", -2294 },
         {"hesse", 6420 },
         {"barracks", -12845 },
         {"commonplaces", -7019 },
         {"befell", -8549 },
         {"faces", -17470 },
         {"scowl", 2592 },
         {"peruvian", -17119 },
         {"yamaha", 1106 },
         {"swamping", -14210 },
         {"class", 9347 },
         {"hypotheses", -10876 },
         {"carbonizer", 5463 },
         {"anabaptists", -1493 },
         {"yuh", -12006 },
         {"knowles", 12364 },
         {"granada", 2272 },
         {"girls", -17347 },
         {"insisted", -790 },
         {"bordeaux", -14751 },
         {"rarer", -17723 },
         {"atreides", 2452 },
         {"unidirectional", -5139 },
         {"upbring", 11279 },
         {"rind", 12473 },
         {"luxembourg", -16645 },
         {"arabian", 10981 },
         {"nonuniform", -5854 },
         {"regalia", -5742 },
         {"appealingly", -4979 },
         {"forecastle", -15303 },
         {"dooley", 11965 },
         {"trappings", -11326 },
         {"rein", -8147 },
         {"corndog", -7822 },
         {"chutes", 125 },
         {"distribution's", -5617 },
         {"outgoing", -17998 },
         {"concourse", 3006 },
         {"spoilers", -17279 },
         {"sanguine", -12207 },
         {"coolheaded", -414 },
         {"camille", -8154 },
         {"davenport", -19512 },
         {"tillers", -14675 },
         {"courtyard", -160 },
         {"inappreciable", -19916 },
         {"spreads", 7597 },
         {"notifying", 2493 },
         {"caliper", -706 },
         {"offsets", -19922 },
         {"jarhead", 4771 },
         {"inroad", -11022 },
         {"brat's", -5060 },
         {"coerces", 3282 },
         {"brought", -11317 },
         {"macromolecular", -1705 },
         {"homologue", 1495 },
         {"truncation", 2830 },
         {"habits", 12554 },
         {"tousle", -16251 },
         {"widths", 7527 },
         {"rectangles", 11751 },
         {"turpitude", -7577 },
         {"dignitary", -13388 },
         {"jig", -8839 },
         {"million", 12548 },
         {"loggers", 996 },
         {"dactyl", -6836 },
         {"experimentation's", 2786 },
         {"maximilian", 3717 },
         {"stretching", 957 },
         {"carlson", -10396 },
         {"starch", -17205 },
         {"keel", 1445 },
         {"caption's", -5070 },
         {"lanced", 2636 },
         {"shania", 1529 },
         {"hockey", -10241 },
         {"panties", -7639 },
         {"breakpoint", -11945 },
         {"unrolling", -10162 },
         {"suggested", -15636 },
         {"volleyball's", -2967 },
         {"maybe", 4778 },
         {"customary", 7647 },
         {"clutched", 5717 },
         {"slack", -9695 },
         {"set", -3626 },
         {"frosted", -4221 },
         {"oxcart", -9909 },
         {"tintype", 123 },
         {"approval", -9462 },
         {"reluctance", -10926 },
         {"paralyzing", 12546 },
         {"brigades", -2849 },
         {"approachable", 236 },
         {"antisubmarine", 12326 },
         {"comely", -14621 },
         {"stormier", -19368 },
         {"drumlin", 2345 },
         {"teamwork", 9096 },
         {"crescents", 1589 },
         {"possibilities", 11949 },
         {"renegade", 11892 },
         {"hoary", -9734 },
         {"structural", -5889 },
         {"sessions", 1760 },
         {"detaining", 11795 },
         {"cumbersome", 3871 },
         {"veronika", -18647 },
         {"authenticity", -12918 },
         {"summand", -19059 },
         {"simulator's", -14282 },
         {"broilers", 4115 },
         {"boughs", 5719 },
         {"columbus", -19403 },
         {"bronzed", -2936 },
         {"positing", -16744 },
         {"untidy", -3029 },
         {"activators", -19925 },
         {"gypsy", -6652 },
         {"prunes", -15673 },
         {"snatches", -9386 },
         {"astm", 2422 },
         {"deficiency", -15895 },
         {"6uldv8", 7765 },
         {"sixpence", -10110 },
         {"paring", -16336 },
         {"launch", -19624 },
         {"fabian", -9478 },
         {"hesse", 6009 },
         {"crows", 9472 },
         {"sported", 12111 },
         {"theoretical", 5190 },
         {"perrin", 8596 },
         {"rankings", -10391 },
         {"dizzy", -13466 },
         {"jimenez", -2412 },
         {"chic", -11364 },
         {"exemplifiers", 10405 },
         {"lager", -1058 },
         {"brookside", -4282 },
         {"sluice", 11346 },
         {"ursuline", 4660 },
         {"patentee", -12934 },
         {"grammatically", 4297 },
         {"typewrite", 5257 },
         {"reelect", 4130 },
         {"hydrangea", 7553 },
         {"neither", -10540 },
         {"bluegrass", 4206 },
         {"shipments", -11867 },
         {"whacked", -6213 },
         {"meddling", -17948 },
         {"finitary", 10556 },
         {"scotia", -2107 },
         {"lana", 9817 },
         {"consul's", -12322 },
         {"upholsterer", 1557 },
         {"agreement", 10193 },
         {"gangrene", -1799 },
         {"never", -5202 },
         {"unesco", 6897 },
         {"concentrates", -2456 },
         {"wu", -12780 },
         {"alignments", 2726 },
         {"assailant's", 7154 },
         {"criss", -6246 },
         {"vulturelike", -12454 },
         {"commenced", -16978 },
         {"plenitude", -8609 },
         {"catherwood", 6488 },
         {"economizes", -1259 },
         {"yarmouth", -10031 },
         {"juniors", -1620 },
         {"depleted", 5807 },
         {"uptrend", -18502 },
         {"numeric", -9131 },
         {"flounce", -2831 },
         {"pots", 9052 },
         {"security", 330 },
         {"colorimetry", -11393 },
         {"underestimated", -15583 },
         {"undirected", -18651 },
         {"peacetime", -9341 },
         {"endings", -17795 },
         {"luminously", -758 },
         {"disability's", -12292 }
    }};

    bloom_filter<S, num_hash_fns, precision> filter;
    for (auto& s : members)
    {
        filter.add(s);
    }

    if (std::all_of(members.cbegin(), members.cend(),
                [&filter](auto const& s) { return filter.test(s); }))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
