/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pwd.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/12 15:22:21 by cdaureo-		  #+#	#+#			 */
/*   Updated: 2025/07/01 17:10:41 by cdaureo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_ms *ms)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = get_env_value(ms->env_list, "PWD");
	if (pwd)
		return (printf("%s\n", pwd), 0);
	else
	{
		if (getcwd(cwd, sizeof(cwd)))
			return (printf("%s\n", cwd), 0);
		else
			return (1);
	}
}
