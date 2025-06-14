/*
 * Professional Hangman Game Implementation
 * Cross-Platform Word Guessing Algorithm with Statistical Analysis
 * Code hints and optimizations by artlest
 * 
 * This implementation demonstrates fundamental C++ programming concepts
 * including string manipulation, boolean logic, and iterative processing
 * Optimized for online IDE execution environments
 */

#include <iostream>     // This is needed for input/output stream operations
#include <string>       // This is needed for string data type and manipulation functions
#include <vector>       // This is needed for dynamic array container operations
#include <algorithm>    // This is needed for standard algorithm functions like find()
#include <iomanip>      // This is needed for output formatting and precision control

using namespace std;    // This eliminates the need for std:: prefix for standard library functions

// Function prototype declarations - defining the interface before implementation
void display_game_header();
void display_hangman_visual(int incorrect_guess_count);
void display_word_progress(const string& target_word, const vector<char>& correctly_guessed_letters);
void display_statistical_summary(int total_games, int successful_completions, int average_attempts);
bool validate_character_input(char user_input);
bool check_letter_in_word(char guessed_letter, const string& target_word);
bool evaluate_game_completion_status(const string& target_word, const vector<char>& correctly_guessed_letters);

int main() {
    // Initializing the primary execution environment
    display_game_header();
    
    // Defining the word repository for the guessing algorithm
    vector<string> word_database = {
        "PROGRAMMING", "ALGORITHM", "FUNCTION", "VARIABLE", 
        "COMPILER", "DEBUGGING", "ITERATION", "PROCESSOR"
    };
    
    // Setting up game session parameters and statistical tracking variables
    const int maximum_game_sessions = 3;           // Limiting execution cycles for online IDE compatibility
    const int maximum_incorrect_attempts = 6;      // Defining the failure threshold boundary
    int total_game_sessions = 0;                   // Initializing the session counter
    int successful_game_completions = 0;           // Tracking successful completion metrics
    int cumulative_attempt_count = 0;              // Accumulating total attempts for statistical analysis
    
    // Implementing the main game iteration loop
    for (int game_session_index = 0; game_session_index < maximum_game_sessions; game_session_index++) {
        // Selecting the target word for the current session
        string target_word = word_database[game_session_index % word_database.size()];
        
        // Initializing session-specific tracking containers
        vector<char> correctly_guessed_letters;     // Storing successful character matches
        vector<char> incorrectly_guessed_letters;   // Tracking failed guess attempts
        int incorrect_guess_counter = 0;            // Counting unsuccessful attempts
        int session_attempt_counter = 0;            // Tracking total attempts for this session
        
        cout << "\n" << string(60, '=') << endl;
        cout << "GAME SESSION " << (game_session_index + 1) << " INITIALIZATION" << endl;
        cout << "Target word length: " << target_word.length() << " characters" << endl;
        cout << string(60, '=') << endl;
        
        // Implementing the character guessing iteration loop
        while (incorrect_guess_counter < maximum_incorrect_attempts) {
            // Displaying the current game state visualization
            display_hangman_visual(incorrect_guess_counter);
            display_word_progress(target_word, correctly_guessed_letters);
            
            // Showing previously attempted characters for reference
            cout << "\nIncorrect guesses: ";
            for (char incorrect_char : incorrectly_guessed_letters) {
                cout << incorrect_char << " ";  // Outputting each failed attempt
            }
            cout << endl;
            
            // Implementing user input collection and validation
            char user_character_input;
            cout << "Enter your character guess: ";
            cin >> user_character_input;
            
            // Converting input to uppercase for consistent processing
            user_character_input = toupper(user_character_input);
            session_attempt_counter++;  // Incrementing the attempt counter
            
            // Validating the character input format
            if (!validate_character_input(user_character_input)) {
                cout << "Invalid input detected. Please enter alphabetic characters only." << endl;
                continue;  // Restarting the iteration cycle
            }
            
            // Checking for duplicate guess prevention
            bool already_guessed = false;
            for (char guessed_char : correctly_guessed_letters) {
                if (guessed_char == user_character_input) {
                    already_guessed = true;  // Setting the duplicate flag
                    break;
                }
            }
            for (char incorrect_char : incorrectly_guessed_letters) {
                if (incorrect_char == user_character_input) {
                    already_guessed = true;  // Setting the duplicate flag
                    break;
                }
            }
            
            if (already_guessed) {
                cout << "Character already processed. Please select a different letter." << endl;
                continue;  // Restarting the iteration cycle
            }
            
            // Processing the character guess against the target word
            if (check_letter_in_word(user_character_input, target_word)) {
                correctly_guessed_letters.push_back(user_character_input);  // Adding to success collection
                cout << "Correct guess! Character found in target word." << endl;
            } else {
                incorrectly_guessed_letters.push_back(user_character_input);  // Adding to failure collection
                incorrect_guess_counter++;  // Incrementing the failure counter
                cout << "Incorrect guess. Remaining attempts: " << (maximum_incorrect_attempts - incorrect_guess_counter) << endl;
            }
            
            // Evaluating game completion conditions
            if (evaluate_game_completion_status(target_word, correctly_guessed_letters)) {
                cout << "\n" << string(50, '*') << endl;
                cout << "SUCCESSFUL COMPLETION ACHIEVED!" << endl;
                cout << "Target word: " << target_word << endl;
                cout << "Session attempts: " << session_attempt_counter << endl;
                cout << string(50, '*') << endl;
                successful_game_completions++;  // Incrementing success metrics
                break;  // Terminating the guessing loop
            }
        }
        
        // Handling game failure scenarios
        if (incorrect_guess_counter >= maximum_incorrect_attempts) {
            display_hangman_visual(incorrect_guess_counter);
            cout << "\n" << string(50, '-') << endl;
            cout << "GAME SESSION TERMINATED" << endl;
            cout << "Target word was: " << target_word << endl;
            cout << "Session attempts: " << session_attempt_counter << endl;
            cout << string(50, '-') << endl;
        }
        
        total_game_sessions++;  // Incrementing total session count
        cumulative_attempt_count += session_attempt_counter;  // Accumulating attempt statistics
    }
    
    // Calculating and displaying comprehensive statistical analysis
    int average_attempts = (total_game_sessions > 0) ? cumulative_attempt_count / total_game_sessions : 0;
    display_statistical_summary(total_game_sessions, successful_game_completions, average_attempts);
    
    return 0;  // Indicating successful program termination
}

// Implementing the application header display function
void display_game_header() {
    cout << string(70, '=') << endl;
    cout << "           PROFESSIONAL HANGMAN GAME IMPLEMENTATION" << endl;
    cout << "         Advanced Word Guessing Algorithm System" << endl;
    cout << "              Cross-Platform Compatible Version" << endl;
    cout << string(70, '=') << endl;
}

// Implementing the visual hangman state representation function
void display_hangman_visual(int incorrect_guess_count) {
    cout << "\nHangman Visualization State:" << endl;
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    
    // Implementing conditional visual element rendering based on failure count
    switch (incorrect_guess_count) {
        case 0:
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            break;
        case 1:
            cout << "  |   O" << endl;  // Rendering the head element
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            break;
        case 2:
            cout << "  |   O" << endl;
            cout << "  |   |" << endl;  // Rendering the body element
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            break;
        case 3:
            cout << "  |   O" << endl;
            cout << "  |  /|" << endl;  // Rendering the left arm element
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            break;
        case 4:
            cout << "  |   O" << endl;
            cout << "  |  /|\\" << endl;  // Rendering both arm elements
            cout << "  |    " << endl;
            cout << "  |    " << endl;
            break;
        case 5:
            cout << "  |   O" << endl;
            cout << "  |  /|\\" << endl;
            cout << "  |  /" << endl;   // Rendering the left leg element
            cout << "  |    " << endl;
            break;
        case 6:
            cout << "  |   O" << endl;
            cout << "  |  /|\\" << endl;
            cout << "  |  / \\" << endl;  // Rendering both leg elements (complete figure)
            cout << "  |    " << endl;
            break;
    }
    cout << "__|__" << endl;
    cout << "Incorrect attempts: " << incorrect_guess_count << "/6" << endl;
}

// Implementing the word progress display function with masking algorithm
void display_word_progress(const string& target_word, const vector<char>& correctly_guessed_letters) {
    cout << "\nWord Progress: ";
    
    // Iterating through each character position in the target word
    for (char word_character : target_word) {
        bool character_revealed = false;
        
        // Checking if the current character has been successfully guessed
        for (char guessed_char : correctly_guessed_letters) {
            if (word_character == guessed_char) {
                character_revealed = true;  // Setting the revelation flag
                break;
            }
        }
        
        // Implementing conditional character display logic
        if (character_revealed) {
            cout << word_character << " ";  // Displaying the revealed character
        } else {
            cout << "_ ";  // Displaying the masking placeholder
        }
    }
    cout << endl;
}

// Implementing comprehensive statistical analysis and reporting function
void display_statistical_summary(int total_games, int successful_completions, int average_attempts) {
    cout << "\n" << string(70, '=') << endl;
    cout << "                    STATISTICAL ANALYSIS REPORT" << endl;
    cout << string(70, '=') << endl;
    
    // Calculating success rate percentage with precision formatting
    double success_rate = (total_games > 0) ? (double)successful_completions / total_games * 100.0 : 0.0;
    
    cout << fixed << setprecision(1);  // Setting decimal precision for statistical output
    cout << "Total Game Sessions Executed: " << total_games << endl;
    cout << "Successful Completions: " << successful_completions << endl;
    cout << "Success Rate Percentage: " << success_rate << "%" << endl;
    cout << "Average Attempts Per Session: " << average_attempts << endl;
    
    // Implementing performance classification logic
    cout << "\nPerformance Classification: ";
    if (success_rate >= 80.0) {
        cout << "EXCELLENT PERFORMANCE" << endl;
    } else if (success_rate >= 60.0) {
        cout << "GOOD PERFORMANCE" << endl;
    } else if (success_rate >= 40.0) {
        cout << "AVERAGE PERFORMANCE" << endl;
    } else {
        cout << "NEEDS IMPROVEMENT" << endl;
    }
    
    // Generating visual progress indicator
    cout << "\nSuccess Rate Visualization: ";
    int progress_bar_length = 20;
    int filled_segments = (int)(success_rate / 100.0 * progress_bar_length);
    
    cout << "[";
    for (int i = 0; i < progress_bar_length; i++) {
        if (i < filled_segments) {
            cout << "█";  // Rendering filled progress segments
        } else {
            cout << "░";  // Rendering empty progress segments
        }
    }
    cout << "] " << success_rate << "%" << endl;
    
    cout << string(70, '=') << endl;
    cout << "Program execution completed successfully." << endl;
}

// Implementing character input validation function
bool validate_character_input(char user_input) {
    // Checking if the input character falls within alphabetic ASCII range
    return (user_input >= 'A' && user_input <= 'Z') || (user_input >= 'a' && user_input <= 'z');
}

// Implementing letter existence verification function
bool check_letter_in_word(char guessed_letter, const string& target_word) {
    // Using the standard library find algorithm for character search
    return target_word.find(guessed_letter) != string::npos;
}

// Implementing game completion status evaluation function
bool evaluate_game_completion_status(const string& target_word, const vector<char>& correctly_guessed_letters) {
    // Iterating through each character in the target word for completion verification
    for (char word_character : target_word) {
        bool character_found = false;
        
        // Checking if the current character exists in the correctly guessed collection
        for (char guessed_char : correctly_guessed_letters) {
            if (word_character == guessed_char) {
                character_found = true;  // Confirming character presence
                break;
            }
        }
        
        // Returning false if any character remains unguessed
        if (!character_found) {
            return false;
        }
    }
    
    return true;  // Confirming complete word revelation
}