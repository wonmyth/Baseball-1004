#include "pch.h"
#include "../baseball/baseball.cpp"
#include <iostream>

using namespace std;

class BaseballFixture : public testing::Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(guessNumber);
			FAIL();
		}
		catch (exception e) {
			// PASS
		}
	}
};
TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber) {
	GuessResult result = game.guess("123");

	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf2Strikes0Balls) {
	GuessResult result = game.guess("120");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(2, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf1Strikes2Balls) {
	GuessResult result = game.guess("132");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(2, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf1Strikes1Balls) {
	GuessResult result = game.guess("102");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(1, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf0Strikes3Balls) {
	GuessResult result = game.guess("312");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(0, result.strikes);
	EXPECT_EQ(3, result.balls);
}
