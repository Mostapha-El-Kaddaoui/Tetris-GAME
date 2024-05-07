#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int list_size = 0; // Global variable for list size

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 15

string next_item;
string next_col;
string next_ty;
class element {
public:
    string type;
    string color;
    element* next_element;
    element* prev_element;
    element* next_color;
    element* next_shape;
    element(string a_type, string a_color) {
        this->color = a_color;
        this->type = a_type;
        next_element = NULL;
        prev_element = NULL;
        next_item = a_color + a_type + " \033[0m";
        next_col = a_color;
        next_ty = a_type;
    }
};



class Game_board {
public:
    string Game_matrix[BOARD_HEIGHT][BOARD_WIDTH];
    int score_value = 0;
    string next_element ;
    element* head = NULL; // Head pointer to the first element

    void insert_in_left(element* ele) {
        if (head == NULL) {
            head = ele;
            return;
        }
        ele->next_element = head;
        head->prev_element = ele;
        head = ele;
    }

    void insert_in_right(element* ele) {
        if (head == NULL) {
            head = ele;
            return;
        }
        element* current = head;
        while (current->next_element != NULL) {
            current = current->next_element;
        }
        current->next_element = ele;
        ele->prev_element = current;
    }

void decaler_list(){/*
        element* current = head;
        while (current->next_element != NULL) {
            current = current->next_element;
        }

        // On a trouvé le premier élément de type "S", maintenant on décale
        head = first_element->next_element;
        if (head != NULL) {
            head->prev_element = NULL;
        }

        element* current = head;
        element* last_element = first_element;

        // Parcours jusqu'au dernier élément de type "S"
        while (current != NULL) {
            if (current->type == "S") {
                last_element = current;
            }
            current = current->next_element;
        }
        last_element->type="M";

        // Reconnexion des éléments
        if (last_element != NULL) {
            last_element->next_element = first_element;
        }
        if (first_element != NULL) {
            first_element->prev_element = last_element;
            first_element->next_element = NULL;
        }*/
    }

    void draw_game(){
        element *current = head;
        int k = 0;
        list_size=0;
        cout <<"\n\033[41m\033[37m SCORE : "<<score_value<<" \033[0m\n"<<endl;
        for(int i = 0; i < BOARD_HEIGHT; i++) {
            for(int j = 0; j < BOARD_WIDTH; j++) {
                if(j < 7 && i < 5) {
                    if(j == 3 && i == 2 && current != NULL) {
                        Game_matrix[i][j] = next_item;
                    } else {
                        Game_matrix[i][j] = " # ";
                    }
                }
                else if(i == 13 && j > 4 && j < 35 && current != NULL) {
                    Game_matrix[i][j] = current->color + current->type + " \033[0m";
                    current = current->next_element;
                    list_size++;
                } else {
                    Game_matrix[i][j] = " . ";
                }
            }
        }
        for(int i = 0; i < BOARD_HEIGHT; i++) {
            for(int j = 0; j < BOARD_WIDTH; j++) {
                cout << Game_matrix[i][j];
            }
            cout << "\n";
        }
    }

    void get_Bonus() {
        element *current = head;
        while (current != NULL && current->next_element != NULL && current->next_element->next_element != NULL) {
            element *next1 = current->next_element;
            element *next2 = next1->next_element;

            if (current->type == next1->type && current->type == next2->type || current->color == next1->color && current->color == next2->color) {
                if(current->type == next1->type && current->type == next2->type){
                    score_value++;
                }if(current->color == next1->color && current->color == next2->color){
                    score_value=score_value+2;
                }
                if(current->prev_element != NULL) {
                    current->prev_element->next_element = next2->next_element;
                } else {
                    head = next2->next_element;
                }
                if(next2->next_element != NULL) {
                    next2->next_element->prev_element = current->prev_element;
                }
                // Adjust current pointer
                current = current->prev_element;
            } else {
                current = current->next_element;
            }
        }
    }
    string Stupid_decision() {
        int randomNum = rand() % 2;
        if (randomNum == 0)
            return "l";
        else
            return "r";
    }
    string Intelig_decision() {
        element* current = head;
        element* index = head;
        while (index->next_element->next_element != NULL) {
            index = index->next_element;
        }
        /*if(current->color==next_col && current->next_element->color==next_col){
            return "l";
        }
        if(current->type==next_ty){
            return "l";
        }
        return "r";*/
        if(current->color==next_col && current->next_element->color==next_col || current->type==next_ty && current->next_element->type==next_ty){
            return "l";
        }else if(index->color==next_col && index->next_element->color==next_col || index->type==next_ty && index->next_element->type==next_ty){
            return "r";
        }else if(current->color==next_col){
            return "l";
        }
        return "r";
    }
};


int main() {
    srand(time(0));
    string list_elems[4] = {" \033[37mS", " \033[37mT", " \033[37mL", " \033[37mC"};
    string list_colors[4] = {"\033[41m", "\033[42m", "\033[44m", "\033[40m"};
    Game_board mylist;
    string input;

    for(int i = 0; i < 5; i++) {
        element* new_element_init = new element(list_elems[rand() % 4], list_colors[rand() % 4]);
        mylist.insert_in_right(new_element_init);
    }
    while (true) {
        element* new_element = new element(list_elems[rand() % 4], list_colors[rand() % 4]);
        mylist.draw_game();
        cin >> input;
        if(input=="ai-1"){
            input=mylist.Stupid_decision();
        }
        else if(input=="ai"){
            input=mylist.Intelig_decision();
        }
        if (input == "r") {
            mylist.insert_in_right(new_element);
        } else if (input == "l") {
            mylist.insert_in_left(new_element);
        }
        mylist.get_Bonus();
        if(list_size > 29) {
            cout << "game_over";
            break;
        }
        //mylist.decaler_list();
    }


    return 0;
}
