/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:30:56 by frbranda          #+#    #+#             */
/*   Updated: 2026/02/25 13:20:43 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

// ── FATAL ERRORS ───────────────────────────────────────────────────────

class ServerException : public std::exception
{
	private:
		std::string _message;
		
	public:
		explicit ServerException(const std::string& message) : _message(message) {};
		~ServerException();
		
		const char* what() const throw()
		{
			return _message.c_str();
		};
};



// ── RECOVERABLE ERRORS ───────────────────────────────────────────────────────

class SocketException : public ServerException
{
	public:
		explicit SocketException(const std::string& message) : ServerException("SocketException()-> " + message) {}
		~SocketException() throw() {}
};

class EpollException : public ServerException
{
	public:
		explicit EpollException(const std::string& message) : ServerException("EpollException()-> " + message) {}
		~EpollException() throw() {}
};

#endif