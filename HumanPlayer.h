class HumanPlayer : public Player {

	public:
		HumanPlayer(int);
		~HumanPlayer();

		const lastMove play();

	private:
		void printHand();
};
