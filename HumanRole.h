class HumanRole : public Role {

	public:
		HumanRole();
		~HumanRole();

		const Message play();

	private:
		void printHand();
};
