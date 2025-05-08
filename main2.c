#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char admin_username[50] = "jawad";

// Define struct user
struct user
{
    char username[50];
    char password[50];
};
struct note
{
    int id;
    char username[50];
    char title[50];
    char description[500];
};

char logedInUserName[50];
int delete_is_runne = 0;
char delete_user[50];

void addUser()
{
    struct user newUser;
    char tempUsername[50], tempPassword[50];
    int user_exist = 0;

    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    FILE *file = fopen("user.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%s %s", tempUsername, tempPassword) == 2)
        {
            if (strcmp(tempUsername, newUser.username) == 0)
            {
                user_exist = 1;
                break;
            }
        }
        fclose(file);
    }

    if (user_exist)
    {
        printf("User already exists\n");
        return;
    }

    FILE *file1 = fopen("user.txt", "a");
    if (file1 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file1, "%s %s\n", newUser.username, newUser.password);
    fclose(file1);

    printf("User added successfully!\n");
}

void removeUser(const char *usernameToRemove)
{
    char tempUsername[50], tempPassword[50];
    int found = 0;

    FILE *file = fopen("user.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while (fscanf(file, "%s %s", tempUsername, tempPassword) == 2)
    {
        if (strcmp(tempUsername, usernameToRemove) != 0)
        {
            // Copy all users except the one to remove
            fprintf(tempFile, "%s %s\n", tempUsername, tempPassword);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("user.txt");
        rename("temp.txt", "user.txt");
        printf("User '%s' removed successfully.\n", usernameToRemove);
    }
    else
    {
        remove("temp.txt");
        printf("User '%s' not found.\n", usernameToRemove);
    }
}

void loginUser()
{
    struct user newUser;
    char tempUsername[50], tempPassword[50];
    int user_exist = 0;

    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    FILE *file = fopen("user.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%s %s", tempUsername, tempPassword) == 2)
        {
            if ((strcmp(tempUsername, newUser.username) == 0) && (strcmp(tempPassword, newUser.password) == 0))
            {
                user_exist = 1;
                break;
            }
        }
        fclose(file);
    }

    if (user_exist == 1)
    {
        printf("Login successful!\n");
        strcpy(logedInUserName, newUser.username);
        if (strcmp(logedInUserName, admin_username) == 0)
        {
            printf("Welcome admin , %s!\n", logedInUserName);
            adminPanel();
        }
        else
        {
            printf("Welcome, %s!\n", logedInUserName);
            userDashboard();
        }
    }
    else
    {
        printf("Invalid username or password!\n");
    }
    fclose(file);
}

void userDashboard()
{
    int choice;

    while (1)
    {
        printf("\n===== USER DASHBOARD =====\n");
        printf("1. Add Note\n");
        printf("2. Show My Notes\n");
        printf("3. Delete Note by ID\n");
        printf("4. Delete All My Notes\n");
        printf("5. Search Note by ID\n");
        printf("6. Edit\n");
        printf("7. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createNote(logedInUserName);
            break;
        case 2:
            showUserNotes(logedInUserName);
            break;
        case 3:
            deleteNote(logedInUserName);
            break;
        case 4:
            deleteNoteByUser(logedInUserName);
            break;
        case 5:
            searchNoteById(logedInUserName);
            break;
        case 6:
            editNote(logedInUserName);
            break;
        case 7:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void adminPanel()
{
    int adminChoice;
    char temp_username[50];
    while (1)
    {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Show Users\n");
        printf("2. Add User\n");
        printf("3. Delete User\n");
        printf("4. Show specific User Notes\n");
        printf("5. Remove specific user notes\n");
        printf("6. Remove specific user notes by note Id\n");
        printf("7. Add note\n");
        printf("8. Edit note\n");
        printf("9. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &adminChoice);

        // Switch block to handle different admin actions
        switch (adminChoice)
        {
        case 1:
            printUsers(); // Show all users (function placeholder)
            break;
        case 2:
            addUser(); // Add a new user (function placeholder)
            break;
        case 3:
            takeInput(temp_username);
            removeUser(temp_username); // Add a new user (function placeholder)
            break;
        case 4:
            takeInput(temp_username);     // Get username input before executing the function
            showUserNotes(temp_username); // Show notes of the user (function placeholder)
            break;
        case 5:
            takeInput(temp_username); // Get username input before executing the function
            deleteNoteByUser(temp_username);
            break;
        case 6:
            takeInput(temp_username); // Get username input before executing the function
            deleteNote(temp_username);
            break;
        case 7:
            takeInput(temp_username);
            createNote(temp_username);
            break;
        case 8:
            // takeInput(temp_username);
            editNote(logedInUserName);
            break; // Logout
        case 9:
            printf("Logging out...\n");
            return; // Logout
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void printUsers()
{
    struct user newUser;
    FILE *file = fopen("user.txt", "r");

    if (file == NULL)
    {
        printf("No users found. The file does not exist.\n");
        return;
    }

    printf("\nStored Users:\n");
    while (fscanf(file, "%s %s", newUser.username, newUser.password) != EOF)
    {
        printf("Username: %s, Password: %s\n", newUser.username, newUser.password);
    }

    fclose(file);
}

void takeInput(char *str)
{
    printf("Enter a username: ");
    scanf("%s", str); // Using scanf to take input from the user
}
// create new notes

void createNote(char username[50])
{
    struct note newNote;
    char *line = NULL;
    size_t len = 0;
    int lastId = 0;
    FILE *file;

    // Read last ID from primarykey.txt
    file = fopen("primarykey.txt", "r");
    if (file != NULL)
    {
        if (fscanf(file, "%d", &lastId) != 1)
        {
            lastId = 0; // In case the file is empty or malformed, set to 0
        }
        fclose(file);
    }

    // Clear any leftover newline characters in input buffer
    getchar();

    // Get the title for the new note
    printf("Enter title: ");
    fgets(newNote.title, sizeof(newNote.title), stdin);
    newNote.title[strcspn(newNote.title, "\n")] = '\0'; // Remove the newline character

    // Get the description for the new note
    printf("Enter description: ");
    fgets(newNote.description, sizeof(newNote.description), stdin);
    newNote.description[strcspn(newNote.description, "\n")] = '\0'; // Remove the newline character

    // Open the file to append the new note
    FILE *file1 = fopen("note.txt", "a");
    if (file1 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // Ensure the note is appended on a new line
    if (lastId > 0)
    {
        fprintf(file1, "\n"); // Add a newline if there are already previous notes
    }

    // Increment the last ID and write the new note to the file
    newNote.id = lastId + 1;
    fprintf(file1, "id:%d username:%s title:%s# description:%s#\n",
            newNote.id, username, newNote.title, newNote.description);

    fclose(file1);

    // Update the last ID in primarykey.txt
    file = fopen("primarykey.txt", "w");
    if (file == NULL)
    {
        printf("Error opening primarykey.txt!\n");
        exit(1);
    }
    fprintf(file, "%d", newNote.id); // Save the updated ID
    fclose(file);

    printf("New note added successfully with ID %d!\n", newNote.id);
}

void showUserNotes(char username[50])
{
    if (delete_user == username && username != '\0' && username != NULL)
    {
        printf("All notes are deleted\n");
        return;
    }
    struct note storedNote;
    int user_exist = 0;
    char *line = NULL;
    size_t len = 0;

    FILE *file = fopen("note.txt", "r");
    if (file != NULL)
    {
        while (getline(&line, &len, file) != -1)
        {
            memset(&storedNote, 0, sizeof(struct note));

            // Parse the line assuming format: id:1 username:john title:MyTitle# description:MyDescription#
            if (sscanf(line, "id:%d username:%49s title:%49[^#]# description:%499[^#]#",
                       &storedNote.id, storedNote.username, storedNote.title, storedNote.description) == 4)
            {
                // Trim trailing spaces
                size_t tlen = strlen(storedNote.title);
                if (tlen > 0 && storedNote.title[tlen - 1] == ' ')
                    storedNote.title[tlen - 1] = '\0';

                tlen = strlen(storedNote.description);
                if (tlen > 0 && storedNote.description[tlen - 1] == ' ')
                    storedNote.description[tlen - 1] = '\0';

                // Match username or show all
                if (username == NULL || username[0] == '\0' || strcmp(storedNote.username, username) == 0)
                {
                    if ((strcmp(logedInUserName, admin_username) == 0) && strcmp(logedInUserName, storedNote.username) != 0)
                    {
                        printf("Note ID: %d\n", storedNote.id);
                        printf("Username: %s\n", storedNote.username);
                        printf("Title: *******\n");
                        printf("Description: *********\n");
                        printf("-------------------------\n");
                        user_exist = 1;
                    }
                    else
                    {
                        printf("Note ID: %d\n", storedNote.id);
                        printf("Username: %s\n", storedNote.username);
                        printf("Title: %s\n", storedNote.title);
                        printf("Description: %s\n", storedNote.description);
                        printf("-------------------------\n");
                        user_exist = 1;
                    }
                }
            }
        }

        if (!user_exist)
        {
            if (username == NULL || username[0] == '\0')
                printf("No notes found for any user.\n");
            else
                printf("No notes found for user: %s\n", username);
        }

        free(line);
        fclose(file);
    }
    else
    {
        printf("Error opening file.\n");
    }
}

void deleteNote(char username[50])
{
    if (delete_user == username && username != '\0' && username != NULL)
    {
        printf("All notes are deleted\n");
        return;
    }

    FILE *fp, *fp1;
    struct note storedNote;
    int id;
    int found = 0;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("note.txt", "r");
    fp1 = fopen("temp_note.txt", "w");
    if (fp == NULL || fp1 == NULL)
    {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    printf("\nEnter Note ID to delete: ");
    scanf("%d", &id);

    while (getline(&line, &len, fp) != -1)
    {
        memset(&storedNote, 0, sizeof(struct note));

        if (sscanf(line, "id:%d username:%49s title:%49[^#]# description:%499[^#]#",
                   &storedNote.id, storedNote.username, storedNote.title, storedNote.description) == 4)
        {

            // Trim trailing spaces in title and description
            size_t tlen = strlen(storedNote.title);
            if (tlen > 0 && storedNote.title[tlen - 1] == ' ')
                storedNote.title[tlen - 1] = '\0';

            tlen = strlen(storedNote.description);
            if (tlen > 0 && storedNote.description[tlen - 1] == ' ')
                storedNote.description[tlen - 1] = '\0';

            // Match username or show all
            if (username == NULL || username[0] == '\0' || strcmp(storedNote.username, username) == 0)
            {
                if (storedNote.id == id)
                {
                    found = 1;
                    continue; // Skip writing this note to the temp file (effectively deleting it)
                }
            }

            fprintf(fp1, "id:%d username:%s title:%s# description:%s#\n",
                    storedNote.id, storedNote.username, storedNote.title, storedNote.description);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found)
    {
        remove("note.txt");
        rename("temp_note.txt", "note.txt");
        printf("Note deleted successfully.\n");
    }
    else
    {
        printf("Note not found.\n");
        remove("temp_note.txt");
    }

    free(line);
}

void deleteNoteByUser(char username[50])
{
    if (delete_user == username && username != '\0' && username != NULL)
    {
        printf("All notes are deleted\n");
        return;
    }

    FILE *fp, *fp1;
    struct note storedNote;
    int found = 0;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("note.txt", "r");
    fp1 = fopen("temp_note.txt", "w");
    if (fp == NULL || fp1 == NULL)
    {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    while (getline(&line, &len, fp) != -1)
    {
        memset(&storedNote, 0, sizeof(struct note));

        if (sscanf(line, "id:%d username:%49s title:%49[^#]# description:%499[^#]#",
                   &storedNote.id, storedNote.username, storedNote.title, storedNote.description) == 4)
        {

            // Trim trailing spaces
            size_t tlen = strlen(storedNote.title);
            if (tlen > 0 && storedNote.title[tlen - 1] == ' ')
                storedNote.title[tlen - 1] = '\0';

            tlen = strlen(storedNote.description);
            if (tlen > 0 && storedNote.description[tlen - 1] == ' ')
                storedNote.description[tlen - 1] = '\0';

            // Delete all notes for the given username
            if (username != NULL && username[0] != '\0' && strcmp(storedNote.username, username) == 0)
            {
                found = 1; // Mark that we deleted a note
                continue;  // Skip writing this note to the temp file
            }

            fprintf(fp1, "id:%d username:%s title:%s# description:%s#\n",
                    storedNote.id, storedNote.username, storedNote.title, storedNote.description);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found)
    {
        remove("note.txt");
        rename("temp_note.txt", "note.txt");
        printf("Note(s) deleted successfully.\n");
        delete_is_runne = 1;
        strcpy(delete_user, username);
    }
    else
    {
        printf("No notes found for the given username.\n");
        remove("temp_note.txt");
    }

    free(line);
}

void editNote(char username[50])
{
    if (delete_user == username && username != '\0' && username != NULL)
    {
        printf("All notes are deleted\n");
        return;
    }
    if (strcmp(logedInUserName, username) != 0)
    {
        printf("You are not the owner of this note\n");
        return;
    }
    FILE *fp = fopen("note.txt", "r");
    FILE *temp = fopen("temp_note.txt", "w");
    struct note storedNote;
    int found = 0;
    int id;
    char *line = NULL;
    size_t len = 0;

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Note ID to search: ");
    scanf("%d", &id);

    while (getline(&line, &len, fp) != -1)
    {
        memset(&storedNote, 0, sizeof(struct note));

        if (sscanf(line, "id:%d username:%49s title:%49[^#]# description:%499[^#]#",
                   &storedNote.id, storedNote.username, storedNote.title, storedNote.description) == 4)
        {

            // Trim trailing spaces

            size_t tlen = strlen(storedNote.title);
            if (tlen > 0 && storedNote.title[tlen - 1] == ' ')
                storedNote.title[tlen - 1] = '\0';

            tlen = strlen(storedNote.description);
            if (tlen > 0 && storedNote.description[tlen - 1] == ' ')
                storedNote.description[tlen - 1] = '\0';

            if (storedNote.id == id &&
                (username == NULL || username[0] == '\0' || strcmp(storedNote.username, username) == 0))
            {
                found = 1;
                printf("Editing Note ID %d:\n", storedNote.id);
                printf("Current Title: %s\n", storedNote.title);
                printf("Current Description: %s\n", storedNote.description);

                printf("Enter new title: ");
                scanf(" %[^\n]", storedNote.title);
                printf("Enter new description: ");
                scanf(" %[^\n]", storedNote.description);
            }

            // Write the updated note to the temp file, adding a newline after each note
            fprintf(temp, "id:%d username:%s title:%s# description:%s#\n",
                    storedNote.id, storedNote.username, storedNote.title, storedNote.description);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("note.txt");
        rename("temp_note.txt", "note.txt");
        printf("Note updated successfully!\n");
    }
    else
    {
        remove("temp_note.txt");
        printf("Note with ID %d not found.\n", id);
    }

    free(line);
}

void searchNoteById(char username[50])
{
    if (delete_user == username && username != '\0' && username != NULL)
    {
        printf("All notes are deleted\n");
        return;
    }
    FILE *fp;
    struct note storedNote;
    int id;
    int found = 0;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("note.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file\n");
        return;
    }

    printf("\nEnter Note ID to search: ");
    scanf("%d", &id);

    while (getline(&line, &len, fp) != -1)
    {
        memset(&storedNote, 0, sizeof(struct note));

        if (sscanf(line, "id:%d username:%49s title:%49[^#]# description:%499[^#]#",
                   &storedNote.id, storedNote.username, storedNote.title, storedNote.description) == 4)
        {

            // Trim trailing spaces
            size_t tlen = strlen(storedNote.title);
            if (tlen > 0 && storedNote.title[tlen - 1] == ' ')
                storedNote.title[tlen - 1] = '\0';

            tlen = strlen(storedNote.description);
            if (tlen > 0 && storedNote.description[tlen - 1] == ' ')
                storedNote.description[tlen - 1] = '\0';

            if (storedNote.id == id)
            {
                if (username == NULL || username[0] == '\0' || strcmp(storedNote.username, username) == 0)
                {

                    if (logedInUserName == admin_username)
                    {
                        printf("Note ID: %d\n", storedNote.id);
                        printf("Username: %s\n", storedNote.username);
                        printf("Title: *******\n");
                        printf("Description: *********\n");
                        printf("-------------------------\n");
                        found = 1;
                    }
                    else
                    {
                        printf("Note ID: %d\n", storedNote.id);
                        printf("Username: %s\n", storedNote.username);
                        printf("Title: %s\n", storedNote.title);
                        printf("Description: %s\n", storedNote.description);
                        printf("-------------------------\n");
                        found = 1;
                    }
                }
                break;
            }
        }
    }

    if (!found)
    {
        printf("Note with ID %d not found or doesn't belong to user %s.\n", id, username);
    }

    fclose(fp);
    free(line);
}

// Main function
int main()
{
    int choice;

    while (1)
    {
        printf("\n===== MENU =====\n");
        printf("1. Add User\n2. Login User\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}
