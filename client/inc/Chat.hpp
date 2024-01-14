/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Chat
*/

/**
 * @file Chat.hpp
 * 
 * @brief Header file for Chat class
 * 
 */

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <chrono>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Coordinator.hpp"
#include "Graphic.hpp"

/**
 * @brief Chat class
 * 
 * @details Chat class for the client
 */
class Chat {
public:
    /**
     * @brief Construct a new Chat object
     * 
     * @param user 
     */
    Chat(std::string user);

    /**
     * @brief Destroy the Chat object
     * 
     */
    ~Chat();

    /**
     * @brief Display the chat window
     * 
     * @param coordinator Reference to the coordinator
     */
    void DisplayChatWindow(Coordinator &coordinator);

    /**
     * @brief Check if the chat window is open
     * 
     * @return true if the chat window is open
     * @return false if the chat window is closed
     */
    bool isOpen(void) {
        return _isOpen;
    }

protected:
    /**
     * @brief Draw the chat window
     * 
     * @param isOpen boolean to know if the chat window is open
     * @param coordinator Reference to the coordinator
     */
    void DrawWindow(bool isOpen, Coordinator &coordinator);

    /**
     * @brief Detect the input of the user
     * 
     */
    void DetectInput(void);

    /**
     * @brief Display the chats
     * 
     */
    void DisplayChats(void);

    /**
     * @brief Display the chat
     * 
     * @param chat chat to display
     * @param y y position of the chat
     */
    void DisplayChat(std::pair<std::string, std::string> chat, int &y); 
private:
    std::vector<std::pair<std::string, std::string>> chatList; ///< List of chats
    bool _isOpen; ///< Boolean to know if the chat window is open
    std::string _chat; ///< Chat
    std::string _user; ///< User
    std::chrono::seconds _duration; ///< Duration
    std::chrono::steady_clock::time_point receiveTime; ///< Receive time
};

#endif /* !CHAT_HPP_ */
