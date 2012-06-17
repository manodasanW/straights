class Role {

	public:
		Role();
		~Role();

		struct Message {

			std::string command;
			Card * card;

		}
		
		virtual const Message play() = 0;

	protected:
		void playCard(const Card&);
		void discardCard(const Card&);
}

namespace helper {

	int findCard(std::vector<const Card*>, const Card);
	void legalMoves(std::vector<const Card*>, std::vector<const Card*>);

}
