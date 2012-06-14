class AIPlayer: public Player {

	public:
		AIPlayer(int);
		~AIPlayer();

		const lastMove play();
};

