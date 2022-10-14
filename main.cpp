# include <iostream>
# include <string>
# include <stdexcept>
# include "subway.h"
# include "doubly.h"

using namespace std;

int main() {

	try {
		DoublyLinkedList<Subway> lst;
		lst.insertAtFront(Subway(10, "Dumb", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "APU"));
		lst.insertAtEnd(Subway(9, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.4, 3, "Zoo Negara"));
		lst.insertAtEnd(Subway(8, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.4, 3, 8, 0.8, 7, "KLCC"));
		lst.insertAtEnd(Subway(7, "Sultan Ismail", "PWTC", "Masjid Jamek", 8, 0.8, 7, 8, 0.8, 7, "Eco Park"));
		lst.insertAtEnd(Subway(6, "Masjid Jamek", "Sultan Ismail", "", 8, 0.8, 7, 0, 0, 0, "APU"));
//		lst.insertItemAt((Subway(11, "Middle", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "APU")), 5);

/*		cout << lst.getNodeAtIndex(3)->data.travelFareBetweenPreviousStation<< endl;
		cout << lst.getNodeAtIndex(3)->data.travelFareBetweenNextStation<< endl;
		cout << endl;
		lst.updateNodeData(0, 100, 2);
		cout << endl;
		cout << lst.getNodeAtIndex(2)->data.travelFareBetweenPreviousStation << endl;
		cout << lst.getNodeAtIndex(3)->data.travelFareBetweenPreviousStation << endl;
		cout << lst.getNodeAtIndex(2)->data.travelFareBetweenNextStation << endl;*/

		lst.showForward(1);
		cout << endl;
		cout << endl;
		lst.sortListAscending();
		lst.showForward(1);
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what()<< endl;
		return 1;
	}
	return 0;
}

