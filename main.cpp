//
//  main.cpp
//
//  Created by Tanay Jaiman on 10/17/23.
//

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/*
    BinarySearchTree Class that implements a Binary Search Tree with the following instance variables
 
    Instance Variable(s) :
        Player structure that contains ->
            - float key          : The key value used for comparison in the BST
            - string player_name : Stores the name of the player
            - string team_name   : Stores the name of the team
            - Player * left      : Pointer to the left Player (Left Child Node)
            - Player * right     : Pointer to the right Player (Right Child Node)
 
        Player * root ->
            Stores the root of the Binary Search Tree
 */
class BinarySearchTree {
private:
    struct Player {
    public:
        float key = 0;      // Initialized to 0
        string player_name;
        string team_name;
        Player * left;
        Player * right;
        Player * parent;
    };
    
public:
    Player * root;
    
    // Constructor that initializes root to NULL
    BinarySearchTree() {
        root = nullptr;
    }
    
    void add_player_data(string, string, float);
    void delete_player(Player *);
    Player * TREE_SUCCESSOR(Player *);
    Player * SEARCH(Player *, string);
    void display_highest();
    void display_lowest();
    void display_descending(Player * player);
    void display_triple_doubles(BinarySearchTree *, BinarySearchTree *);
    vector<Player*> find_all(Player *, int);
    void display(Player * player);
    
    // returns true if BST is empty and false otherwise
    bool is_empty() { return (root == nullptr); }
};

int main(int argc, const char * argv[]) {
    // Instantiating the three BSTs for points, assists, and rebounds
    BinarySearchTree points_bst, assists_bst, rebounds_bst = BinarySearchTree();
    int choice, data_type = 0; // User input variables
    
    // Instantiating Player information variables
    float player_data;
    string team_name, player_name;
    
    while (true) {
        // Program UI and set of operations
        cout << endl;
        cout << " Basketball Player Statistics" << endl;
        cout << " ----------------------------" << endl;
        cout << " 1. Add Player" << endl;
        cout << " 2. Delete a Player" << endl;
        cout << " 3. Display Highest" << endl;
        cout << " 4. Display Lowest" << endl;
        cout << " 5. Display Triple Doubles" << endl;
        cout << " 6. Display all players in Points Category (descending)" << endl;
        cout << " 7. Exit" << endl;
        cout << endl;
        
        // Prompt the user of input
        cout << " Enter your choice : ";
        cin >> choice;
        
        switch (choice) {
            // Add player using user input into appropriate BST
            case 1:
                cout << endl;
                
                // Prompt the user for the BST they want to modify
                cout << " Data Type (1 : Points, 2 : Assists, 3 : Rebounds) : ";
                cin >> data_type;
                
                // Prompt the user to enter Player information
                cout << endl;
                cout << " Player Name : ";
                cin.ignore();
                getline(cin, player_name);
                
                cout << " Team Name : ";
                getline(cin, team_name);
                
                cout << " Player Data (Points, Assists, Rebounds) : ";
                cin >> player_data;
                
                switch (data_type) {
                    // Add into the Points BST
                    case 1:
                        points_bst.add_player_data(player_name, team_name, player_data);
                        break;
                    
                    // Add into the Assists BST
                    case 2:
                        assists_bst.add_player_data(player_name, team_name, player_data);
                        break;
                    
                    // Add into the Rebounds BST
                    case 3:
                        rebounds_bst.add_player_data(player_name, team_name, player_data);
                        break;
                        
                    default:
                        cout << " Invalid input." << endl;
                        break;
                }
                
                break;
                
            // Delete a player using user input from the appropriate BST
            case 2 :
                cout << endl;
                
                // Prompt the user to input the BST they want to modify
                cout << " Data Type (1 : Points, 2 : Assists, 3 : Rebounds) : ";
                cin >> data_type;
                
                // Prompt the user for the name of player they want to delete
                cout << " Enter the Player's Name : ";
                cin.ignore();
                getline(cin, player_name);
                
                switch (data_type) {
                    // Delete from the Points BST
                    case 1:
                        points_bst.delete_player(points_bst.SEARCH(points_bst.root, player_name));
                        break;
                        
                    // Delete from the Assists BST
                    case 2:
                        assists_bst.delete_player(assists_bst.SEARCH(assists_bst.root, player_name));
                        break;
                    
                    // Delete from the Rebounds BST
                    case 3:
                        rebounds_bst.delete_player(rebounds_bst.SEARCH(rebounds_bst.root, player_name));
                        break;
                        
                    default:
                        break;
                }
                
                break;
            
            // Display the highest values in all three BSTs
            case 3:
                cout << endl;
                cout << " ---- POINTS ----" << endl;
                points_bst.display_highest();
                cout << endl;
                
                cout << " ---- ASSISTS ----" << endl;
                assists_bst.display_highest();
                cout << endl;
                
                cout << " ---- REBOUNDS ----" << endl;
                rebounds_bst.display_highest();
                cout << endl;
                
                break;
                
            // Display the lowest values in all three BSTs
            case 4:
                cout << endl;
                cout << " ---- POINTS ----" << endl;
                points_bst.display_lowest();
                cout << endl;
                
                cout << " ---- ASSISTS ----" << endl;
                assists_bst.display_lowest();
                cout << endl;
                
                cout << " ---- REBOUNDS ----" << endl;
                rebounds_bst.display_lowest();
                cout << endl;
                
                break;
                
            // Displays player with a triple double i.e. players with key > 10.0 in all three BSTs
            case 5:
                cout << endl;
                cout << " Players with a Triple Double!" << endl;
                points_bst.display_triple_doubles(&assists_bst, &rebounds_bst);
                cout << endl;
                break;
                
            // Display all values stored in Points BST in decreasing order
            case 6:
                cout << endl;
                cout << " Displaying player information in decreasing order of points!";
                points_bst.display_descending(points_bst.root);
                break;
                
            // Exit the program
            case 7:
                system("pause");
                return 0;
                break;
                
            default:
                system(" Invalid input.");
                break;
        }
    }
}

/*
     void add_player_data(string [player_name], string [team_name], float [key]) ->
        Adds player to the BST according to the key using the given information
 */
void BinarySearchTree::add_player_data(string player_name, string team_name, float player_data) {
    
    // Initializing a new Player pointer
    Player * new_player = new Player;
    new_player->player_name = player_name;
    new_player->team_name = team_name;
    new_player->key = player_data;
    
    // If the BST is empty, add at root
    if (is_empty()) {
        root = new_player;
        return;
    }
    
    // Else find the parent of the Player to be added
    Player * parent = nullptr;
    Player * iterator = root;
    
    while (iterator) {
        parent = iterator;
        
        if (player_data < iterator->key) iterator = iterator->left;
        else iterator = iterator->right;
    }

    // Add at parent according to the BST rules using comparison
    if (player_data < parent->key) parent->left = new_player;
    else parent->right = new_player;
    
    new_player->parent = parent;
}

/*
    void delete_player(Player * [player]) ->
        Deletes the player from the BST. Uses help from TREE_SUCCESSOR and SEARCH
 */
void BinarySearchTree::delete_player(Player * player) {
    // If player is not found, display "No such player."
    if (player->player_name == "not found") {
        delete player;
        cout << " No such player." << endl;
        return;
    }
    
    // If the only Player is being removed, nullify the root in BST
    if (player == root && player->left == nullptr && player->right == nullptr) {
        root = nullptr;
        return;
    }
    
    Player * temp_node_x = nullptr;
    Player * temp_node_y = nullptr;
    
    // If node has 0 or 1 children
    if (!player->left || !player->right) {
        temp_node_y = player;
    }
    
    // If node has 2 children
    else temp_node_y = TREE_SUCCESSOR(player);
    
    // If temp_node_y has child on left, temp_node_x points to that child
    if (temp_node_y->left) {
        temp_node_x = temp_node_y->left;
    }
    
    // Else temp_node_x points to the one on the right
    else temp_node_x = temp_node_y->right;
    
    // If temp_node_x is not empty (i.e. temp_node_y has children) parent of y is now also parent of x
    if (temp_node_x) {
        temp_node_x->parent = temp_node_y->parent;
    }
    
    // If y is NULL then, x is the root
    if (!temp_node_y) root = temp_node_x;
    
    else {
        if (temp_node_y->parent) {
            if (temp_node_y->parent->left == temp_node_y) temp_node_y->parent->left = temp_node_x;
            else temp_node_y->parent->right = temp_node_x;
        }
    }
    
    if (player != temp_node_y) player->key = temp_node_y->key;
    
    delete temp_node_y;
}

/*
    Player * TREE_SUCCESSOR(Player * [player]) ->
        Returns the Player pointer pointing to the next highest value in the BST
 */
BinarySearchTree::Player * BinarySearchTree::TREE_SUCCESSOR(Player * player) {
    Player * iterator = player;
    
    // If node has a child on right, find the shortest value in that sub-tree which is also the successor
    if (iterator->right) {
        iterator = iterator->right;
        
        while (iterator->left) {
            iterator = iterator->left;
        }
    }
    
    // Else iterate through the parents to find root of sub-tree, parent of that sub-tree is the successor
    else {
        if (!iterator->parent) {
            cout << " Successor does not exist!" << endl;
        }
        
        while (iterator->parent && iterator->parent->right == iterator) {
            iterator = iterator->parent;
        }
        
        iterator = iterator->parent;
    }
    return iterator;
}

/*
    Player * SEARCH(Player * [player], string [player_name]) ->
        Searches in the BST starting from the [player] pointer provided for the Player with Player.player_name == [player_name]
 */
BinarySearchTree::Player * BinarySearchTree::SEARCH(Player * player, string player_name) {
    // New player initialized to Player.player_name = "not found"
    Player * output = new Player;
    output->player_name = "not found";
    
    // Iterate through the sub-BST to find the Player with Player.player_name = [player_name]
    if (player) {
        if (player->player_name == player_name) {
            return player;
        }
        
        if (player->left) output = SEARCH(player->left, player_name);
        if (output->player_name != "not found") return output;
        
        output = SEARCH(player->right, player_name);
        if (output->player_name != "not found") return output;
    }
    
    return output;
}

/*
    void display_highest() ->
        Displays the highest value in a BST. Uses the help of display(Player *) method.
 */
void BinarySearchTree::display_highest() {
    // If BST is empty, display "Nothing to display."
    if (is_empty()) {
        cout << " Nothing to display." << endl;
        return;
    }

    // Else find the rightmost Player in the BST and display it
    Player * iterator = root;
    
    while (iterator->right) {
        iterator = iterator->right;
    }
    
    display(iterator);
}

/*
    void display_lowest() ->
        Displays the lowest value in a BST. Uses the help of display(Player *) method.
 */
void BinarySearchTree::display_lowest() {
    // If BST is empty, display "Nothing to display."
    if (is_empty()) {
        cout << " Nothing to display." << endl;
        return;
    }
    
    // Else find the left-most value in the BST and display it
    Player * iterator = root;
    
    while (iterator->left) {
        iterator = iterator->left;
    }
    
    display(iterator);
}

/*
    void display_descending(Player * [player]) ->
        Displays all the values in the BST with root = [player] in descending order.
 */
void BinarySearchTree::display_descending(Player * player) {
    // Similar to inorder_walk, iterate through each Player starting from the right-most value (max)
    if (player) {
        display_descending(player->right);
        cout << endl;
        display(player);
        display_descending(player->left);
    }
}

/*
    void display(Player * [iterator]) ->
        Displays the player name, team name, and player data associated with [iterator]
 */
void BinarySearchTree::display(Player * iterator) {
    cout << "  - Player Name : " << iterator->player_name << endl;
    cout << "  - Team Name   : " << iterator->team_name << endl;
    cout << "  - Player Data : " << iterator->key << endl;
}

/*
    vector<Player*> find_all(Player* [player], int [key]) ->
        finds and returns a vector of all the values in the BST with root = [player] that have key value >= [key]
 */
vector<BinarySearchTree::Player *> BinarySearchTree::find_all(Player * player, int key) {
    vector<Player*> output;
    
    if (player) {
        if (player->key >= key) output.push_back(player);
        
        vector<Player*> left_result = find_all(player->left, key);
        for (int i = 0; i < left_result.size(); i++) output.push_back(left_result[i]);
        
        vector<Player*> right_result = find_all(player->right, key);
        for (int i = 0; i < right_result.size(); i++) output.push_back(right_result[i]);
    }
    
    return output;
}

/*
    void display_triple_doubles(BinarySearchTree * tree1, BinarySearchTree * tree2) ->
        Displays all the player names of Player(s) that exist in all three BSTs (Points, Assists, Rebounds) with key value >= 10.0
 */
void BinarySearchTree::display_triple_doubles(BinarySearchTree * tree1, BinarySearchTree * tree2) {
    vector<Player*> output, triple_double;
    
    float key = 10.0;
    
    // Find all the Players with key value >= 10 and store it in output list
    Player * iterator = root;
    output = find_all(iterator, key);
    
    Player * search_one, * search_two = new Player;
    for (int i = 0; i < output.size(); i++) {
        // Search for all the players in output in Assists and Rebounds BSTs
        search_one = SEARCH(tree1->root, output[i]->player_name);
        search_two = SEARCH(tree2->root, output[i]->player_name);
        
        // If Player is found and has key value >= 10 in both the BSTs, add it to triple_double list
        if (search_one->key >= key && search_two->key >= key) {
            triple_double.push_back(output[i]);
        }
    }
    
    // Display "No Triple-Doubles to display!" if triple_double list is empty.
    if (triple_double.size() == 0) cout << endl << "No Triple-Doubles to display!" << endl;
    
    // Display all the values in triple_double
    for (int j = 0; j < triple_double.size(); j++) {
        cout << endl;
        cout << "  - Player Name : " << triple_double[j]->player_name;
    }
}

