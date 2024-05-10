#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int list_size = 0; // Global variable for list size

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 15
string decision_data_dec[20];
string decision_data_next[20];
string decision_data_first[20];
string decision_data_last[20];
string next_item;
string next_col;
string next_ty;
int score_value = 0;
int score_max = 0;
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
    string next_element ;
    element* head = NULL; // Head pointer to the first element
    string get_first_type(){
        return head->type;
    }
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
        cout <<"\033[45m\033[37m MAX SCORE : "<<score_max<<" \033[0m"<<endl;
        cout <<"\033[41m\033[37m SCORE : "<<score_value<<" \033[0m\n"<<endl;
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
            return "g";
        }else if(index->color==next_col && index->next_element->color==next_col || index->type==next_ty && index->next_element->type==next_ty){
            return "d";
        }else if(current->color==next_col){
            return "g";
        }
        return "r";
    }
    string supervised_app(){
        string input="r";
        for(int i=0;i<20;i++){
            if(next_ty+ " \033[0m"==decision_data_next[i] && this->get_first_type()+ " \033[0m"==decision_data_first[i]){
                input=decision_data_dec[i];
                cout << "trouver ! "<<endl;
                break;
            }
        }
        return input;
    }
};

void score_saving(string name){
    if(score_max<score_value){
        score_max=score_value;
    }
    ofstream outfile("score.txt", std::ios::app);
    outfile <<name<<" : "<<score_value<<endl;
    outfile.close();
}

void get_menu(){
    cout <<"\n##############################################################\n"<<endl;
    cout <<"[1]- Start New Game"<<endl;
    cout <<"[2]- Start Game"<<endl;
    cout <<"[3]- Quit Game"<<endl;
    cout <<"\n##############################################################\n"<<endl;
}

int main() {
    srand(time(0));
    string list_elems[4] = {" \033[37mS", " \033[37mT", " \033[37mL", " \033[37mC"};
    string list_colors[4] = {"\033[41m", "\033[42m", "\033[44m", "\033[40m"};
    string name="guest";
    int j=0;
    Game_board mylist;
    string input;
    cout << " _____    _        _        ____                      \n";
    cout << "|_   _|__| |_ _ __(_)___   / ___| __ _ _ __ ___   ___ \n";
    cout << "  | |/ _ \\ __| '__| / __| | |  _ / _` | '_ ` _ \\ / _ \\\n";
    cout << "  | |  __/ |_| |  | \\__ \\ | |_| | (_| | | | | | |  __/\n";
    cout << "  |_|\\___|\\__|_|  |_|___/  \\____|\\__,_|_| |_| |_|\\___|\n\n";

    get_menu();
    for(int i = 0; i < 5; i++) {
        element* new_element_init = new element(list_elems[rand() % 4], list_colors[rand() % 4]);
        mylist.insert_in_right(new_element_init);
    }
    while (true) {

    cout <<"[d]- Insert in right"<<endl;
    cout <<"[g]- Insert in left"<<endl;
    cout <<"[ai-s]- Random decision algo"<<endl;
    cout <<"[ai-i]- Inteligente decision algo"<<endl;
    cout <<"[app]- Learned algorithm\n"<<endl;
        element* new_element = new element(list_elems[rand() % 4], list_colors[rand() % 4]);
        mylist.draw_game();
        cin >> input;
        if(input=="ai-s"){
            input=mylist.Stupid_decision();
        }if(input=="ai-i"){
            input=mylist.Intelig_decision();
        }if(input == "d"){
            input = "r";
            decision_data_dec[j]="r";
            decision_data_next[j]=next_ty+ " \033[0m";
            decision_data_first[j]=mylist.get_first_type()+ " \033[0m";
            j++;
        }else if(input == "g"){
            input = "l";
            decision_data_dec[j]="l";
            decision_data_next[j]=next_ty+ " \033[0m";
            decision_data_first[j]=mylist.get_first_type()+ " \033[0m";
            j++;
        }if(input == "ap"){
            input=mylist.supervised_app();
            cout << input<<endl;
        }
        if(input == "3"){
            for(int i=0;i<20;i++){
                cout << decision_data_dec[i]<<" "<<decision_data_next[i]<<" "<<decision_data_first[i]<<endl;
            }
        }
        if (input == "r") {
            mylist.insert_in_right(new_element);
        } else if (input == "l") {
            mylist.insert_in_left(new_element);
        }
        mylist.get_Bonus();

        if(list_size > 29) {
            cout << " @@@@@@@@   @@@@@@   @@@@@@@@@@   @@@@@@@@ \n";
            cout << "@@@@@@@@@  @@@@@@@@  @@@@@@@@@@@  @@@@@@@@ \n";
            cout << "!@@        @@!  @@@  @@! @@! @@!  @@!      \n";
            cout << "!@!        !@!  @!@  !@! !@! !@!  !@!      \n";
            cout << "!@! @!@!@  @!@!@!@!  @!! !!@ @!@  @!!!:!   \n";
            cout << "!!! !!@!!  !!!@!!!!  !@!   ! !@!  !!!!!:   \n";
            cout << ":!!   !!:  !!:  !!!  !!:     !!:  !!:      \n";
            cout << ":!:   !::  :!:  !:!  :!:     :!:  :!:      \n";
            cout << " ::: ::::  ::   :::  :::     ::    :: :::: \n";
            cout << " :: :: :    :   : :   :      :    : :: ::  \n";
            cout << "                                           \n";
            cout << "                                           \n";
            cout << " @@@@@@   @@@  @@@  @@@@@@@@  @@@@@@@      \n";
            cout << "@@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@     \n";
            cout << "@@!  @@@  @@!  @@@  @@!       @@!  @@@     \n";
            cout << "!@!  @!@  !@!  @!@  !@!       !@!  @!@     \n";
            cout << "@!@  !@!  @!@  !@!  @!!!:!    @!@!!@!      \n";
            cout << "!@!  !!!  !@!  !!!  !!!!!:    !!@!@!       \n";
            cout << "!!:  !!!  :!:  !!:  !!:       !!: :!!      \n";
            cout << ":!:  !:!   ::!!:!   :!:       :!:  !:!     \n";
            cout << "::::: ::    ::::     :: ::::  ::   :::     \n";
            cout << " : :  :      :      : :: ::    :   : :     \n\n";

            cout<<"Please enter your name to save the score"<<endl;
            cin>>name;
            score_saving(name);
            break;
        }
        system("clear");
        //mylist.decaler_list();
    }


    return 0;
}
