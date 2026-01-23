/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:03:23 by frbranda          #+#    #+#             */
/*   Updated: 2025/12/18 15:09:01 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_HPP
# define COLOR_HPP

/**
 * @brief ANSI escape codes for terminal text color formatting.
 * 
 * Usage example:
 * 	std::cout << R << "This is red text." << RST << std::endl;
 * 	std::cout << BOLD_B << "This is bold blue text." << RST << std::endl;
 * 
 * @details
 * Includes regular and bold color definitions for standard foreground colors.
 * 
 * @warning Always use 'RST' after a color constant to
 *			avoid unintentional styling.
 * 
 * @category
 * - RESET: Resets all styles to default.
 * - Regular Colors: BLACK, R (Red), G (Green), Y (Yellow), B (Blue),
 *					 M (Magenta), C (Cyan), W (White).
 * - Bold Colors: BOLD_<COLOR> for bold versions of regular colors.
 */

/* RESET / CLEAR*/
/** @brief Reset all text formatting. */
# define RST	"\033[0m"

/** @brief Clear screen */
# define CLEAR		"\033[2J\033[H"

/* Regular Colors */
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

/* Bold Colors */
# define BOLD_BLACK	"\033[1;30m"
# define BOLD_R		"\033[1;31m"
# define BOLD_G		"\033[1;32m"
# define BOLD_Y		"\033[1;33m"
# define BOLD_B		"\033[1;34m"
# define BOLD_M		"\033[1;35m"
# define BOLD_C		"\033[1;36m"
# define BOLD_W		"\033[1;37m"

/* Background colors */
# define BG_BLACK	"\033[40m"
# define BG_R		"\033[41m"
# define BG_G		"\033[42m"
# define BG_Y		"\033[43m"
# define BG_B		"\033[44m"
# define BG_M		"\033[45m"
# define BG_C		"\033[46m"
# define BG_W		"\033[47m"

/* Bright Foreground */
# define BRIGHT_BLACK	"\033[90m"
# define BRIGHT_R		"\033[91m"
# define BRIGHT_G		"\033[92m"
# define BRIGHT_Y		"\033[93m"
# define BRIGHT_B		"\033[94m"
# define BRIGHT_M		"\033[95m"
# define BRIGHT_C		"\033[96m"
# define BRIGHT_W		"\033[97m"

/* Bright Background */
# define BG_BRIGHT_BLACK	"\033[100m"
# define BG_BRIGHT_R		"\033[101m"
# define BG_BRIGHT_G		"\033[102m"
# define BG_BRIGHT_Y		"\033[103m"
# define BG_BRIGHT_B		"\033[104m"
# define BG_BRIGHT_M		"\033[105m"
# define BG_BRIGHT_C		"\033[106m"
# define BG_BRIGHT_W		"\033[107m"


/** @brief White text, Red background */
# define WR_BG		"\033[1;97;41m"  // bold white + red background



/* ************************************************************************* */
/*                                                                           */
/*                              CUSTOM RGB COLORS                            */
/*                                                                           */
/* ************************************************************************* */

 /**
 * @brief 24-bit (TrueColor) ANSI escape codes for custom RGB colors.
 * 
 * These macros allow you to specify any RGB color combination (0–255)
 * for both text (foreground) and background in the terminal.
 * They work in most modern terminal emulators that support TrueColor.
 * 
 * @usage
 *  Example usage:
 *		std::cout << RGB(255, 0, 0) << "Red text"
 *				  << RST << std::endl;
 *		std::cout << BG_RGB(0, 255, 0) << "Green background"
 *				  << RST << std::endl;
 *		std::cout << RGB_COMBO(255,255,255, 0,0,0)
 *				  << "White text on black background" << RST << std::endl;
 * 
 * @details
 *	- `RGB(r,g,b)` sets the text (foreground) color.
 *	- `BG_RGB(r,g,b)` sets the background color.
 *	- `RGB_COMBO(fr,fg,fb, br,bg,bb)` sets both.
 *	- The *_BOLD variants add the bold modifier for
 *	  brighter or emphasized colors.
 * 
 * @note RGB values must be integers in the range [0–255].
 * @warning Always reset color formatting with `RST`
 * 			to avoid leaking styles.
 * 
 * @category
 *  - Normal: RGB(), BG_RGB(), RGB_COMBO()
 *  - Bold:   RGB_BOLD(), BG_RGB_BOLD(), RGB_COMBO_BOLD()
 */


# define RGB(r, g, b)		"\033[0;38;2;" #r ";" #g ";" #b "m"
# define BG_RGB(r, g, b)	"\033[0;48;2;" #r ";" #g ";" #b "m"

# define RGB_COMBO(fr, fg, fb, br, bg, bb) \
	"\033[38;2;" #fr ";" #fg ";" #fb ";48;2;" #br ";" #bg ";" #bb "m"

	
/* Bold variants */
# define RGB_BOLD(r, g, b) "\033[1;38;2;" #r ";" #g ";" #b "m"
# define BG_RGB_BOLD(r, g, b) "\033[1;48;2;" #r ";" #g ";" #b "m"
	
# define RGB_COMBO_BOLD(fr, fg, fb, br, bg, bb) \
	"\033[1;38;2;" #fr ";" #fg ";" #fb ";48;2;" #br ";" #bg ";" #bb "m"

#endif