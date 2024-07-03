#include <stdexcept>
using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};
class Baseball {
public:
	explicit Baseball(const string& question)
		:question(question) {
	}
	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);

		if (guessNumber == question) {
			return { true, MAX_NUMBER, 0 };
		}

		for (int i = 0; i < MAX_NUMBER; i++) {
			if (guessNumber[i] == question[i]) {
				result.strikes++;
			}
			else {
				for (int j = 0; j < MAX_NUMBER; j++) {
					if (i == j) continue;
					if (guessNumber[i] == question[j])
						result.balls++;
				}
			}
		}		
		return { false, result.strikes, result.balls };
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != MAX_NUMBER) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");

		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	bool isDuplicatedNumber(const string& guessNumber) {
		return (guessNumber[0] == guessNumber[1] ||
			guessNumber[1] == guessNumber[2] ||
			guessNumber[2] == guessNumber[0]);
	}

	const int MAX_NUMBER = 3;
private:
	string question;
	GuessResult result = { false, 0, 0 };
};