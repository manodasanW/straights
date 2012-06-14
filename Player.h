class Player {
	public:
		Player(int);
		virtual ~Player();

		virtual const lastMove play() = 0;
		void legalMoves(std::vector<Card*>);
		void newRound (std::vector<Card*>);

		int id() const;
		int score() const;

		void updateScore();

		struct lastMove {

			std::string move;
			Card* card;	

		};
			
	protected:
		void playCard(const Card&);
		void discardCard(const Card&);
	private:
		std::vector<const Card*> hand;
		std::vector<const Card*> discards;
		int score;
		int id;
};

namespace helper {

	int findCard(std::vector<const Card*>, const Card);

}
