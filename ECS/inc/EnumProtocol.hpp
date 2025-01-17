/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EnumProtocol
*/

/**
 * @file EnumProtocol.hpp
 * @brief Header file defining enums and protocol vectors.
 */

#ifndef ENUMPROTOCOL_HPP_
#define ENUMPROTOCOL_HPP_

#include <vector>

/**
 * @enum Cmd
 * @brief Enumerates different command types.
 */
enum Cmd {
    RESPONSE = 0, /**< Response command. */
    CONNECT = 1, /**< Connect command. */
    PARAM = 2, /**< Parameter command. */
    ACTION = 3, /**< Action command. */
    POS = 4, /**< Position command. */
    PING = 5, /**< Ping command. */
    PONG = 6, /**< Pong command. */
    DISCONNECT = 7, /**< Quit command. */
    CREATE_ROOM_CMD = 14, /**< Create room command. */
    SPRITE = 16, /**< Create sprite command. */
};

/**
 * @enum Action
 * @brief Enumerates different action types.
 */
enum Action {
    READY = 8, /**< Ready action. */
    START = 9, /**< Start action. */
    SHOOT = 10, /**< Shoot action. */
    MOVE = 11, /**< Move action. */
    DESTROY = 12, /**< Destroy command. */
    CREATE = 13, /**< Create command. */
    MESSAGE_SEND = 15, /**< Send message command. */
};

/**
 * @enum Error
 * @brief Enumerates different error types.
 */
enum Error {
    OK = 0, /**< OK error. */
    PASS = 1, /**< Pass error. */
    UNKNOW = 2, /**< Unknown error. */
    ALREADY_START = 3, /**< Already started error. */
    ALREADY_STOP = 4, /**< Already stopped error. */
    FAIL_CONNECT = 5, /**< Failed to connect error. */
    FAIL_START = 6, /**< Failed to start error. */
    CREATE_ROOM = 7, /**< Failed to create room error. */
    STOP_SEND = 8, /**< Send to stop send this packet. */
    UNVAILABLE_MOVE = 9, /**< Failed move error. */
    NO_RIGHT = 10, /**< Permission denied for cmd. */
};

/** 
 * @brief Vector representing a CONNECT command.
 */
static const std::vector<int> _CONNECT = {Cmd::CONNECT, 1};

/** 
 * @brief Vector representing a PING command.
 */
static const std::vector<int> _PING = {Cmd::PING, 0};

/** 
 * @brief Vector representing a PONG command.
 */
static const std::vector<int> _PONG = {Cmd::PONG, 1};

/** 
 * @brief Vector representing an UNKNOWN error response.
 */
static const std::vector<int> _UNKNOW = {Cmd::RESPONSE, 1, Error::UNKNOW};

/** 
 * @brief Vector representing a FAIL_CONNECT error response.
 */
static const std::vector<int> _FAIL_CONNECT = {Cmd::RESPONSE, 1, Error::FAIL_CONNECT};

static const std::vector<int> _CREATE_ROOM = {Cmd::RESPONSE, 1, Error::CREATE_ROOM};

static const std::vector<int> _STOP_SEND = {Cmd::RESPONSE, 1, Error::STOP_SEND};

static const std::vector<int> _UNVAILABLE_MOVE = {Cmd::RESPONSE, 1, Error::UNVAILABLE_MOVE};

/** 
 * @brief Vector representing an OK response.
 */
static const std::vector<int> _OK = {Cmd::RESPONSE, 1, Error::OK};

/** 
 * @brief Vector representing a PASS response.
 */
static const std::vector<int> _PASS = {Cmd::RESPONSE, 1, Error::PASS};

static const std::vector<int> _MOVE = {Action::MOVE, 2};

#endif /* !ENUMPROTOCOL_HPP_ */
