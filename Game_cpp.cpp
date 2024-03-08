#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 15
void hello(){
    cout<< "hello";
}

class element{
    public:
        string type;
        string color;
        element *next_element;
        element *prev_eleme­nt;
        element(string a_type,string a_color){
            this->color=a_color;
            this->type=a_type;
        }

};
class listelems{
    public:
        element *head;
        int score_value=0;
        string score_name[6]={"S ","C ","O ","R ","E ",": "};
        int order[22]={0,1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,20,21};
        int list_count=0;
    public:
        listelems(){
            head=NULL;
        }
        void insert_elem(string type,string color){
            element *new_element=new element(type,color);
            new_element->next_element=head;
            if(head!=NULL){
                head->prev_eleme­nt=new_element;
            }
            head=new_element;
            list_count++;
        }
        void delete_elem(element *current) {
            if (current == NULL) {
                return;
            }
            if (current->prev_eleme­nt != NULL) {
                current->prev_eleme­nt->next_element = current->next_element;
            }
            if (current->next_element != NULL) {
                current->next_element->prev_eleme­nt = current->prev_eleme­nt;
            }
            delete current;
        }
        void printlist(){
            element *current=head;
            int k=0;
            int d=0;
            int alternat=0;
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    if(j<7 && i<5){
                        if(j==3 && i==2 && current!=NULL){
                            if(current->type!="N"){
                                cout<<current->type<<" ";
                            }
                            current=current->next_element;
                        }else{
                            cout << "# ";
                        }
                    }//else if(i==12 && j>8 && j<31){
                       // cout <<order[d]<<" ";
                        //d++;
                    //}
                    else if(i==13 && j>8 && j<31 && current!=NULL){
                            if(current->type!="N"){
                                cout << current->type<<" ";
                                alternat++;
                            }
                            current=current->next_element;
                    }else if(j>30 && j<38 && i==2){
                        if(j<37){
                            cout<< this->score_name[k];
                            k++;
                        }else{
                            cout<< this->score_value <<" ";
                        }
                    }else{
                        cout << ". ";
                    }
                }
                cout << "\n";
            }
        }
        void getBonus() {
            element *current = head;
            while (current != NULL && current->next_element != NULL && current->next_element->next_element != NULL) {
                element *next1 = current->next_element;
                element *next2 = next1->next_element;

                if (current->type == next1->type && current->type == next2->type) {
                    current->type = "N";
                    next1->type = "N";
                    next2->type = "N";
                }

                current = current->next_element;
            }
        }
};

int main() {
    string input;
    srand(time(0));
    string list_elems[4] = {"S", "T", "L", "C"};
    listelems mylist;

    cout << "## MENU :##########################\n";
    cout << "(a) - Start TETRIS GAME\n";
    cout << "(q) - Quit GAME\n";
    cout << "###################################\n";

    while (true) {
        cin >> input;
        if (input == "a") {
            mylist.insert_elem(list_elems[rand() % 4], "RED");
            mylist.printlist();
            mylist.getBonus();
        } else if (input == "q") {
            cout << "Exiting game.\n";
            break;
        } else {
            cout << "Invalid input. Please enter 'a' to start the game or 'q' to quit.\n";
        }
    }

    return 0;
}
