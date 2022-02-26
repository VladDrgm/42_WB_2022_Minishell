/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:44 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:46:44 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	isascii() checks whether c is a 7-bit unsigned char value that fits into
	the ASCII character set.
RETURN VALUE
	The values returned are nonzero if the character c falls into the
	tested class, and zero if not.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c < 128);
}
