#include "Role.h"

class Player {
	public:
		Player(int, bool);
		virtual ~Player();

		const Message play();
		void newRound (std::vector<Card*>);
		void updateScore();

		int id() const;
		int score() const;

	private:
		Role role;
		std::vector<const Card*> hand;
		std::vector<const Card*> discards;
		int score;
		int id;
};
