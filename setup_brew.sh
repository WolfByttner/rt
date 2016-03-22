# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup_brew.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/22 15:03:22 by jbyttner          #+#    #+#              #
#    Updated: 2016/03/22 15:04:14 by jbyttner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

brew update
brew tap homebrew/versions
mkdir -p ~/Library/Caches/Homebrew/Formula
brew install glfw3
