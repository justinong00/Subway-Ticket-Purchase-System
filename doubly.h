#ifndef DOUBLY_H_
#define DOUBLY_H_

# include <string>
# include <stdexcept>
# include <iomanip>  	// std::setprecision
# include "subway.h"

using namespace std;

template<typename T> // abstract type
class DoublyNode {

	public:
		T data;
		DoublyNode<T> *prev;
		DoublyNode<T> *next;
};

template<typename T>
class DoublyLinkedList {

	public:
		DoublyNode<T> *head;
		DoublyNode<T> *tail;
		int size;

		DoublyLinkedList() {
			this->size = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}

		int getSize() {
			return size;
		}

		void showForward() {
			if (size > 0) {
				DoublyNode<T> *current = head;
				while (current != nullptr) {
					cout << current->data << " ";
					current = current->next;
				}
			}
			else
				throw runtime_error("The list is empty");
		}

		void showBackward() {

			if (size > 0) {
				DoublyNode<T> *current = tail;
				while (current != nullptr) {
					cout << current->data << " ";
					current = current->prev;
				}
			}
			else
				throw runtime_error("The list is empty");
		}

		void showForwardEachNodeAndItsNextNode() {
			if (size > 0)
				if (size > 1) {
					DoublyNode<T> *current = head;
					for (int i = 0; i < size - 1; i++) {	// size - 1 because tail node's next is nullptr
						cout << current->data << " -> " << current->next->data<< endl;
						current = current->next;
					}
				}
				else
					throw runtime_error("There is only one node in the list");
			else
				throw runtime_error("The list is empty");
		}

		void showBackwardEachNodeAndItsPreviousNode() {
			if (size > 0)
				if (size > 1) {
					DoublyNode<T> *current = tail;
					for (int i = 0; i < size - 1; i++) {	// size - 1 because head node's prev is nullptr
						cout << current->data << " -> " << current->prev->data << endl;
						current = current->prev;
					}
				}
				else
					throw runtime_error("There is only one node in the list");
			else
				throw runtime_error("The list is empty");
		}

		void showNextNodesAfterIndex(int index) {
			// direction: head to tail. For e.g, B (start): C, D, E, etc. (Next Nodes)
			if (size > 0)
				if (size > 1)
					if (index >= 0 && index < size) {
						if (index == size - 1)
							cout << "No Next Nodes. Index " << index << " is the tail node." << endl;
						else if (index < size / 2) {
							DoublyNode<T> *current = head;
							for (int i = 0; i < index; i++)
								current = current->next;
							while (current->next != nullptr) {
								cout << current->next->data << endl;
								current = current->next;
							}
						}
						else {
							DoublyNode<T> *current = tail;
							for (int i = 0; i < size - (index + 1); i++)	// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
								current = current->prev;
							while (current->next != nullptr) {
								cout << current->next->data << endl;
								current = current->next;
							}
						}
					}
					else
						throw invalid_argument("Invalid index provided");
				else
					throw runtime_error("There is only one node in the list");
			else
				throw runtime_error("The list is empty");
		}

		void showPreviousNodesAfterIndex(int index) {
			// direction: tail to head. For e.g, E (start): D, C, B, etc. (Previous Nodes)
			if (size > 0)
				if (size > 1)
					if (index >= 0 && index < size) {
						if (index == 0)
							cout << "No Previous Nodes. Index " << index << " is the head node." << endl;
						else if (index < size / 2) {
							DoublyNode<T> *current = head;
							for (int i = 0; i < index; i++)
								current = current->next;
							while (current->prev != nullptr) {
								cout << current->prev->data << endl;
								current = current->prev;
							}
						}
						else {
							DoublyNode<T> *current = tail;
							for (int i = 0; i < size - (index + 1); i++)	// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
								current = current->prev;
							while (current->prev != nullptr) {
								cout << current->prev->data << endl;
								current = current->prev;
							}
						}
					}
					else
						throw invalid_argument("Invalid index provided");
				else
					throw runtime_error("There is only one node in the list");
			else
				throw runtime_error("The list is empty");
		}

		void insertAtFront(T elem) {
			DoublyNode<T> *newNode = new DoublyNode<T>;
			newNode->data = elem;
			newNode->next = head;
			newNode->prev = nullptr;
			head = newNode;

			if (tail == nullptr)	// empty list
				tail = newNode;
			else
				newNode->next->prev = newNode;
			size++;
		}

		void insertAtEnd (T elem) {
			DoublyNode<T> *newNode = new DoublyNode<T>;
			newNode->data = elem;
			newNode->next = nullptr;
			newNode->prev = tail;
			tail = newNode;

			if (head == nullptr)	// empty list
				head = newNode;
			else
				newNode->prev->next = newNode;
			size++;
		}

		void insertItemAt(T elem, int index) {
			if (index >= 0 && index <= size)	// (index <= size) because 4 nodes, 5 placement options (b4 A, after A, B, C, D), --index as argument
				if (index == 0)
					insertAtFront(elem);
				else if (index == size)
					insertAtEnd(elem);
				else if (index < size / 2) {	// means index can be reached faster with head node
					DoublyNode<T> *newNode = new DoublyNode<T>;
					newNode->data = elem;

					DoublyNode<T> *current = head;
					for (int i = 0; i < index; i++)
						current = current->next;

					newNode->next = current;
					newNode->prev = current->prev;
					current->prev->next = newNode; 	// preceeding node links to the newNode
					current->prev = newNode;		// following node links to the newNode
					size ++;
				}
				else {							// index closer to tail node
					DoublyNode<T> *newNode = new DoublyNode<T>;
					newNode->data = elem;

					DoublyNode<T> *current = tail;
					for (int i = 0; i < size - index; i++)		// going in reverse
						current = current->prev;

					newNode->next = current->next;
					newNode->prev = current;
					current->next->prev = newNode; 	// following node links to the newNode
					current->next = newNode;		// preceeding node links to the newNode
					size ++;
				}
			else
				throw invalid_argument("Invalid index provided");
		}

	    DoublyNode<T> *getNodeAtIndex(int index) {
	    	if (size > 0)
	    		if (index >= 0 && index < size) {
	    			if (index < size / 2) {
	    				DoublyNode<T> *current = head;
	    				for (int i = 0; i < index; i++)
	    					current = current->next;
	    				return current;
	    			}
	    			else {
	    				DoublyNode<T> *current = tail;
	    				for (int i = 0; i < size - (index + 1); i++)	// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
	    					current = current->prev;
	    				return current;
	    			}
	    		}
	    		else
	    			throw invalid_argument("Invalid index provided");
	    	else
	    		throw runtime_error("The list is empty");
	    }

	    void updateNodeData(int index, double newData) {
	    	DoublyNode<T> *ptr = this->getNodeAtIndex(index);
	    	ptr->data = newData;
	    }

	    // method overload, to pass in string data type to modify data
	    void updateNodeData(int index, string newData) {
	    	DoublyNode<T> *ptr = this->getNodeAtIndex(index);
	    	ptr->data = newData;
	    }

	    double getDataDifferenceBetweenTwoNodes(int start_index, int destination_index) {
	    	double return_value = 0;

	    	if (start_index >= 0 && start_index <= size && destination_index >= 0 && destination_index <= size) {
	    		// SWAPPING for reverse search for e.g., start index (8), destination index (1)
	    		if (destination_index < start_index) {
	    			int temp = destination_index;
	    			destination_index = start_index;
	    			start_index = temp;
	    		}
	    		// traverse the doubly linked list starting from head node only since swapping is done
	    		DoublyNode<T> *current = head;
	    		for (int i = 0; i < start_index; i++)
	    			current = current->next;
	    		for (int i = 0; i < destination_index - start_index; i++) {
	    			return_value += current->data;
	    			current = current->next;
	    		}
	    		return return_value;
	    	}
	    	else
	    		throw invalid_argument("Invalid index provided");
	    }

	    void sortListAscending() {
	    	DoublyNode<T> *i, *j;
	    	T temp;

	    	if (head == nullptr) {
	    		throw runtime_error("The list is empty");
	    	}
	    	else {
	    		for (i = head; i->next != nullptr; i = i->next)
	    			for (j = i->next; j != nullptr; j = j->next)
	    				if (i->data > j->data) {
	    					temp = i->data;
	    					i->data = j->data;
	    					j->data = temp;
	    				}
	    	}
	    }

		void deleteBeginning() {
			if (size > 0) {
				DoublyNode<T> *current = head;
				head = current->next;
				current->next->prev = nullptr;
				delete current;
				size--;
			}
			else
				throw runtime_error("The list is empty");
		}

		void deleteEnd() {
			if (size > 0) {
				DoublyNode<T> *current = tail;
				tail = current->prev;
				current->prev->next = nullptr;
				delete current;
				size--;
			}
			else
				throw runtime_error("The list is empty");
		}

		void deleteItemAt(int index) {
			if (index >= 0 && index < size)
				if (index == 0)
					deleteBeginning();
				else if (index == size - 1)
					deleteEnd();
				else if (index < size / 2) {	// means index can be reached faster with head node
					DoublyNode<T> *current = head;
					for (int i = 0; i < index; i++)
						current = current->next;

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
					size --;
				}
				else {							// index closer to tail node
					DoublyNode<T> *current = tail;
					for (int i = 0; i < size - (index + 1); i++)		// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
						current = current->prev;

					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
					size --;
				}
			else
				throw invalid_argument("Invalid index provided");
		}

		//method overload, method body defined outside class
		void showForward(int mode) {}

		//method overload, method body defined outside class
		void showBackward(int mode) {}

		//method overload, method body defined outside class
		void updateNodeData(int index, double newData, int mode) {}

		//method body defined outside class NEW
		void updateNodeData(int index, string T::*member, string newData) {}

		// method body defined outside class NEW
		void updateNodeData(int index, double T::*member, double newData) {}

		//method overload, method body defined outside class
		double getDataDifferenceBetweenTwoNodes(int start_index, int destination_index, int mode) {return 0;}

		// method body defined outside class NEW
		void formatInfoTabsForTable(string info) {};

		// method body defined outside class NEW
		void showForwardAllInfoInTable() {};

};

// !!Not yet complete the different mode for each subway member
template<>
void DoublyLinkedList<Subway> :: showForward(int mode) {
	if (size > 0) {
		DoublyNode<Subway> *current = head;
		int opt = 1;
		while (current != nullptr) {
			if (mode == 1)
				cout << current->data.subwayId << " ";
			else if (mode == 2)
				cout << current->data.currentStationName << endl;
			else if (mode == 3)
				cout << current->data.travelFareBetweenNextStation << " ";
			else if (mode == 4)
				cout << current->data.travelFareBetweenPreviousStation << " ";
			else if (mode == 5)
				cout << current->data.travelTimeBetweenNextStation << " ";
			else if (mode == 6)
				cout << current->data.travelTimeBetweenNextStation << " ";
			else if (mode == 7) 	// for selecting a station.
				cout << opt << ". " <<  current->data.currentStationName << endl;
			else if (mode == 8) 	// for selecting a station.
				cout << current->data.nearbySightseeingSpots << " ";
			current = current->next;
			opt++;
		}
	}
	else
		cout << "The list is empty" << endl;
}

// !!Not yet complete the different mode for each subway member
template<>
void DoublyLinkedList<Subway> :: showBackward(int mode) {
	if (size > 0) {
		DoublyNode<Subway> *current = tail;
		while (current != nullptr) {
			if (mode == 1)
				cout << current->data.subwayId << " ";
			if (mode == 2)
				cout << current->data.currentStationName << endl;
			current = current->prev;
		}
	}
	else
		cout << "The list is empty" << endl;
}

// only require this to show one subway station name and its following subway station name (forward routes)
template<>
void DoublyLinkedList<Subway> :: showForwardEachNodeAndItsNextNode() {
	if (size > 0)
		if (size > 1) {
			DoublyNode<Subway> *current = head;
			int opt = 1;
			for (int i = 0; i < size - 1; i++) {	// size - 1 because tail node's next is nullptr
				cout << opt << ". " << current->data.currentStationName << " -> " << current->next->data.currentStationName << endl;
				current = current->next;
				opt++;
			}
		}
		else
			throw runtime_error("There is only one station in the list");
	else
		throw runtime_error("The list is empty");
}

// only require this to show one subway station name and its previous subway station name (return routes)
template<>
void DoublyLinkedList<Subway> :: showBackwardEachNodeAndItsPreviousNode() {
	if (size > 0)
		if (size > 1) {
			DoublyNode<Subway> *current = tail;
			for (int i = 0; i < size - 1; i++) {	// size - 1 because head node's prev is nullptr
				cout << current->data.currentStationName << " -> " << current->prev->data.currentStationName << endl;
				current = current->prev;
			}
		}
		else
			throw runtime_error("There is only one node in the list");
	else
		throw runtime_error("The list is empty");
}

// only require this to show available destinations from selected subway station (forward route)
template<>
void DoublyLinkedList<Subway> :: showNextNodesAfterIndex(int index) {
	// direction: Titiwangsa -> Chan Sow Line. For e.g: Titiwangsa (Depart): PWTC, Sultan Ismail, Masjid Jamek, etc. (Destinations)
	if (size > 0)
		if (size > 1)
			if (index >= 0 && index < size) {
				if (index == size - 1)
					cout << "None. It is END-OF-LINE" << endl;
				if (index < size / 2) {
					DoublyNode<Subway> *current = head;
					for (int i = 0; i < index; i++)
						current = current->next;
					while (current->next != nullptr) {
						cout << current->next->data.currentStationName << endl;
						current = current->next;
					}
				}
				else {
					DoublyNode<Subway> *current = tail;
					for (int i = 0; i < size - (index + 1); i++)	// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
						current = current->prev;
					while (current->next != nullptr) {
						cout << current->next->data.currentStationName << endl;
						current = current->next;
					}
				}
			}
			else
				throw invalid_argument("Invalid index provided");
		else
			throw runtime_error("There is only one station in the list");
	else
		throw runtime_error("The list is empty");
}

// only require this to show available destinations from selected subway station (return route)
template<>
void DoublyLinkedList<Subway> :: showPreviousNodesAfterIndex(int index) {
	// direction: Chan Sow Lin -> Titiwangsa. For e.g: Chan Sow Lin (Depart): Pudu, Hang Tuah, Plaza Rakyat, etc. (Destinations)
	if (size > 0)
		if (size > 1)
			if (index >= 0 && index < size) {
				if (index == 0)
					cout << "None. It is END-OF-LINE" << endl;
				else if (index < size / 2) {
					DoublyNode<Subway> *current = head;
					for (int i = 0; i < index; i++)
						current = current->next;
					while (current->prev != nullptr) {
						cout << current->prev->data.currentStationName << endl;
						current = current->prev;
					}
				}
				else {
					DoublyNode<Subway> *current = tail;
					for (int i = 0; i < size - (index + 1); i++)	// size - (index + 1) to have the pointer land on the correct node (without it, will move one additional node)
						current = current->prev;
					while (current->prev != nullptr) {
						cout << current->prev->data.currentStationName << endl;
						current = current->prev;
					}
				}
			}
			else
				throw invalid_argument("Invalid index provided");
		else
			throw runtime_error("There is only one station in the list");
	else
		throw runtime_error("The list is empty");
}

// only require this to change travel fare (mode 1, mode 2) and travel time (mode 3, mode 4) between subway stations
template<>
void DoublyLinkedList<Subway> :: updateNodeData(int index, double newData, int mode) {
	// the difference between index and size must always be less than 2 for the program to work properly, because 4 stations, 3 routes, user option will be decremented by 1 furthermore as index.

	// Mode Option
	// 1. Modify fare for forward routes.
	// 2. Modify fare for return routes.
	// 3. Modify time for forward routes.
	// 4. Modify time for return routes.
	if (mode == 1) {
		DoublyNode<Subway> *ptr = this->getNodeAtIndex(index);
		if (index < size - 1) {		// if true, means its last station for forward route, so next fare should not be assigned.
			ptr->data.travelFareBetweenNextStation = newData;
			ptr = ptr->next;
			ptr->data.travelFareBetweenPreviousStation = newData;
		}
		else
			throw invalid_argument("Invalid index provided. the difference between index and size must always be less than 2 when user select from route menu");
	}
	else if (mode == 2) {
		DoublyNode<Subway> *ptr = this->getNodeAtIndex(size - (index + 1));	// (index + 1) to have the pointer land on the correct node in the function (without it, will move one additional node)
		if (index < size - 1) {		// if true, means its last station for return route, so previous fare should not be assigned.
			ptr->data.travelFareBetweenPreviousStation = newData;
			ptr = ptr->prev;
			ptr->data.travelFareBetweenNextStation = newData;
		}
		else
			throw invalid_argument("Invalid index provided. the difference between index and size must always be less than 2 when user select from route menu");
	}
	else if (mode == 3) {
		DoublyNode<Subway> *ptr = this->getNodeAtIndex(index);
		if (index < size - 1) {		// if true, means its last station for forward route, so next time should not be assigned.
			ptr->data.travelTimeBetweenNextStation = newData;
			ptr = ptr->next;
			ptr->data.travelTimeBetweenPreviousStation = newData;
		}
		else
			throw invalid_argument("Invalid index provided. the difference between index and size must always be less than 2 when user select from route menu");
	}
	else if (mode == 4) {
		DoublyNode<Subway> *ptr = this->getNodeAtIndex(size - (index + 1));	// (index + 1) to have the pointer land on the correct node in the function (without it, will move one additional node)
		if (index < size - 1) {		// if true, means its last station for return route, so previous time should not be assigned.
			ptr->data.travelTimeBetweenPreviousStation = newData;
			ptr = ptr->prev;
			ptr->data.travelTimeBetweenNextStation = newData;
		}
		else
			throw invalid_argument("Invalid index provided. the difference between index and size must always be less than 2 when user select from route menu");
	}
	else
		throw invalid_argument("Invalid mode provided. Mode between 1 to 4 only");
}

// only require this to update Subway member variable with string data type
template<>
void DoublyLinkedList<Subway> :: updateNodeData(int index, string Subway::*member, string newData) {
	DoublyNode<Subway> *ptr = this->getNodeAtIndex(index);
		ptr->data.*member = newData;	// *member: pointer-to-member concept
}

// only require this to update Subway member variable with double data type
template<>
void DoublyLinkedList<Subway> :: updateNodeData(int index, double Subway::*member, double newData) {
	DoublyNode<Subway> *ptr = this->getNodeAtIndex(index);
		ptr->data.*member = newData;	// *member: pointer-to-member concept
}

// only require this to compare distance, fare and time between two stations
template<>
double DoublyLinkedList<Subway> :: getDataDifferenceBetweenTwoNodes(int start_index, int destination_index, int mode) {
	double return_value = 0;

	if (start_index >= 0 && start_index <= size && destination_index >= 0 && destination_index <= size)
		if (mode >= 1 && mode <= 3) {
			// station menu will display 1. Titiwangsa....... 8. Chan Sow Lin. User can select two station (start and destination station) to compare.
			// if user's selection is return route (Start: 8. Chan Sow Lin, Destination: 1. Tititwangsa), need to do SWAPPING of index because programme traverse linked list from head node only
			// since for e.g., Chan Sow Lin -> Titiwangsa has the same distance, fare, time as Titiwangsa -> Chan Sow Lin, SWAPPING will still produce correct result.
			if (destination_index < start_index) {
				int temp = destination_index;
				destination_index = start_index;
				start_index = temp;
			}
			// traverse the doubly linked list starting from head node only since swapping is done
			DoublyNode<Subway> *current = head;
			for (int i = 0; i < start_index; i++)
				current = current->next;
			for (int i = 0; i < destination_index - start_index; i++) {
				if (mode == 1)
					return_value += current->data.travelDistanceBetweenNextStation;
				if (mode == 2)
					return_value += current->data.travelFareBetweenNextStation;
				if (mode == 3)
					return_value += current->data.travelTimeBetweenNextStation;
				current = current->next;
			}
			return return_value;
		}
		else
			throw invalid_argument("Invalid mode provided. Mode between 1 to 3 only");
	else
		throw invalid_argument("Invalid index provided");
}

// !!Not yet complete, need to sort member variables after subwayId
template<>
void DoublyLinkedList<Subway> :: sortListAscending() {
	DoublyNode<Subway> *i, *j;
	int temp;

	if (head == nullptr) {
		throw runtime_error("The list is empty");
	}
	else {
		for (i = head; i->next != nullptr; i = i->next)
			for (j = i->next; j != nullptr; j = j->next)
				if (i->data.subwayId > j->data.subwayId) {
					temp = i->data.subwayId;
					i->data.subwayId = j->data.subwayId;
					j->data.subwayId = temp;
				}
	}
}

// to format tabs depending on length of string data for table view
template<>
void DoublyLinkedList<Subway> :: formatInfoTabsForTable(string info) {
	if (info.length() < 8) {
		cout << info << "\t\t\t";
	}
	else {
		cout << info << "\t\t";
	}
}

// to display all subway details in table view
template<>
void DoublyLinkedList<Subway> :: showForwardAllInfoInTable() {
	if (size > 0) {
		cout << "Subway ID\tCurrent Station Name\tPrevious Station Name\tNext Station Name\t"
				<< "Distance To Prev.\tFare To Prev.\tTime To Prev.\t"
				<< "Distance To Next.\tFare To Next.\tTime To Next.\t"
				<< "Nearby Sigtseeing Spots"
		<< endl;
		cout << "================================================================================================================="
				<< "================================================================================================================="
				<< "================================================================================================================="
		<< endl;
		DoublyNode<Subway> *current = head;
		while (current != nullptr) {
			cout << current->data.subwayId << "\t\t";
			formatInfoTabsForTable(current->data.currentStationName);
			formatInfoTabsForTable(current->data.previousStationName);
			formatInfoTabsForTable(current->data.nextStationName);
			cout << setprecision(2) << fixed;	// shows two decimal places
			cout << current->data.travelDistanceBetweenPreviousStation << "\t\t\t";
			cout << current->data.travelFareBetweenPreviousStation << "\t\t";
			cout << current->data.travelTimeBetweenPreviousStation << "\t\t";
			cout << current->data.travelDistanceBetweenNextStation << "\t\t\t";
			cout << current->data.travelFareBetweenNextStation << "\t\t";
			cout << current->data.travelTimeBetweenNextStation << "\t\t";
			cout << setprecision(0) << fixed;	// reset the setprecision output buffer to not affect following output
			cout << current->data.nearbySightseeingSpots << endl;;
			current = current->next;
		}
	}
	else
		cout << "The list is empty" << endl;
}

#endif
