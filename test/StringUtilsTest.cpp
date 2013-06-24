
#include <mvcgame/util/StringUtils.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace mvcgame;

TEST(StringUtils, trim) {

    std::string test = "      aaa  ";
    StringUtils::ltrim(test);

    ASSERT_EQ("aaa  ", test);

    StringUtils::rtrim(test);

    ASSERT_EQ("aaa", test);
}

TEST(StringUtils, base64) {

    std::string test = "testing ñàñá";
    std::string resp = StringUtils::base64Encode(test);

    ASSERT_EQ("dGVzdGluZyDDscOgw7HDoQ==", resp);

    resp = StringUtils::base64Decode(resp);

    ASSERT_EQ(test, resp);
}