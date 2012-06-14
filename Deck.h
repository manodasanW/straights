class Deck {
	
	public:
		Deck();
		~Deck();
		void shuffle();
		vector<const Card*> dealPlayerHand();
		friend std::ostream &operator<<(std::ostream &, Deck &);

	private:
		vector<const Card*> cards;

};

std::ostream &operator<<(std::ostream &, Deck &);
