/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/04/10 01:20:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	mychild(t_solib *solib, t_sofork_child *child)
{
	(void)solib;
	int received_num;
	char	*reponse;

	received_num = child->get->integer(child->this->read);
	printf("Message reçu du processus parent : %d\n", received_num);
	reponse = child->get->string(solib, child->this->read);
	child->send->string(child->this->write, reponse);
	printf("Message reçu du processus parent : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = child->get->string(solib, child->this->read);
	child->send->string(child->this->write, reponse);
	printf("Message reçu du processus parent : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = child->get->string(solib, child->this->read);
	child->send->string(child->this->write, reponse);
	printf("Message reçu du processus parent : %s\n", reponse);
	solib->free(solib, reponse);
	


	child->send->string(child->this->write, "Salut parent !");
	child->send->string(child->this->write, "je suis un message test");
	child->send->string(child->this->write, "effectivement ca fais beaucoup de message mais oklm");

	//child->send->integer(child->this->write, str_exec(solib, "ls -la"));
	return (0);
}

//que peux-til y avoir d'interessant dans un pipex ?
// les commande executer
// les sortie de c'est command
// // j'ai deja l'entré et la sortie de mon pipex grace au tuto
// mon but est juste de rediré un flux vers un fd final 

int	solib_validfd(int fd)
{
	if (fd < 0 || fd > 1024 || read(fd, 0, 0) < 0)
		return (FALSE);
	return (TRUE);
}


int	pipexchild(t_solib *solib, t_sofork_child *child)
{
	t_sofork_parent	*parent;
	
	char **commands;
	int	index;
	int status;
	int in;
	int out;

	commands = child->get->strings(solib, child->this->read);
	index = child->get->integer(child->this->read);
	in = child->get->integer(child->this->read);
	out = child->get->integer(child->this->read);
	if (index < 0)
	{
		printf("command : [invalide command] -- index : %d\n", index);
		printf("Return process pipe : [%d] -- [%d]\n", in, out);
		// return du process avant la fin
		child->send->integer(child->this->write, in);
		child->send->integer(child->this->write, out);
		child->send->string(child->this->write, "SUCCES");
		return (0);
	}
	else
		printf("command : [%s] -- index : %d\n", commands[index], index);

	
	parent = solib->new->fork(solib, pipexchild);
	parent->send->strings(parent->this->write, commands);
	parent->send->integer(parent->this->write, index - 1);
	parent->send->integer(parent->this->write,in);
	parent->send->integer(parent->this->write, parent->pipes->child->write);
	waitpid(parent->pid->child, &status, 0);

	// recevoir les valeur de retour
	int new_in;
	int new_out;
	char *reponse;
	
	new_in = parent->get->integer(parent->this->read);
	new_out = parent->get->integer(parent->this->read);
	reponse = parent->get->string(solib, parent->this->read);
	
	printf("in : %d out : %d | EXECUTION ------- : %s\n",new_in, new_out, commands[index]);
	printf("%d - LAST REPONSE -- %d -- %d : %s\n",status, new_in, new_out, reponse);
	child->send->integer(child->this->write, parent->pipes->child->read);
	child->send->integer(child->this->write, out);
	child->send->string(child->this->write, commands[index]);

	//execution en dernier
	solib->exec(solib, commands[index], in,	out);
	return (0);
}

// si je veux ecrire a mon parent de dois write dans le fd 6 et il dois lire dans le fd 5
// 

char	*solib_pipex(t_solib *solib, int in, int out, char **commands)
{
	t_sofork_parent	*parent;
	int	lenght;

	lenght = 0;
	while (commands[lenght])
		lenght++;
	printf("lenght : %d\n", lenght);
	
	int	status;

	(void)out;
	parent = solib->new->fork(solib, pipexchild);
	parent->send->strings(parent->this->write, commands);
	parent->send->integer(parent->this->write, lenght - 1);
	parent->send->integer(parent->this->write, in);
	parent->send->integer(parent->this->write, out);
	waitpid(parent->pid->child, &status, 0);

	// recevoir les valeur de retour
	int new_in;
	int new_out;
	char *reponse;
	
	new_in = parent->get->integer(parent->this->read);
	new_out = parent->get->integer(parent->this->read);
	reponse = parent->get->string(solib, parent->this->read);
	printf("%d -PIPEX LAST REPONSE -- %d -- %d : %s\n",status, new_in, new_out, reponse);
	printf("enfant terminé ! status : %d\n", status);
	
	// recuperer ce qu'il y a dans out pour le return 
	return ("SUCCES");
}

int solib_pipex_openfd(char *path_in, char *path_out, int *in, int *out)
{
	*in = open(path_in, O_RDWR , 0644);
	if (*in < 0)
		return (1);
	*out = open(path_out, O_RDWR , 0644);
	if (*out < 0)
		return (close(*in), 1);
	printf("fd in : %d -- fd out : %d\n", *in, *out);
	return (0);
}

char *read_file(t_solib *solib, int fd, int size)
{
	char	*buf;
	char	*data;

	data = ft_strdup(solib, "");
	buf = ft_memalloc(solib, sizeof(char) * size);
	while (read(fd, buf, size) > 0)
		ft_strmcat(solib, &data, buf);
	solib->free(solib, buf);
	return (data);
}



int main(int argc, char **argv, char **envp) {
	t_solib	*solib;
	//t_sofork_parent *parent;
	//char	*reponse;
	char	**commands;
	int		i;

	solib = sonew(argc, argv, envp);

	commands = solib->malloc(solib, sizeof(char *) * solib->cmd->argc - 2);
	i = 0;
	while (solib->cmd->argv[i + 1] && solib->cmd->argv[i + 2])
	{
		commands[i] = solib->cmd->argv[i + 1];
		i++;
	}
	commands[i] = 0;
	ft_putstrs(2, commands);
	int fdin;
	int fdout;

	if (solib_pipex_openfd(solib->cmd->argv[0], solib->cmd->argv[solib->cmd->argc - 1], &fdin, &fdout))
		return (printf("erreur l'ors de l'ouverture des fd pour pipex\n"), 1);

	//solib->exec(solib, "grep zoyern.*", fdin , fdout);
	solib_pipex(solib, fdin, fdout, commands);
	/*printf("--------reponse de la commande : \n%s\n--------------fin de la reponse de la commande\n", reponse);
	solib->free(solib, reponse);
	
	reponse = solib->shell(solib, "ls -la");
	//printf("--------reponse de la commande : \n%s\n--------------fin de la reponse de la commande\n", reponse);
	solib->free(solib, reponse);

	parent = solib->new->fork(solib, mychild);
	parent->send->integer(parent->this->write, 50);
	parent->send->string(parent->this->write, "salut mon enfant !");
	parent->send->string(parent->this->write, "je suis un message test");
	parent->send->string(parent->this->write, "mon enfant vas pas aimé autant de chaine de caractere");

	
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);
	reponse = parent->get->string(solib, parent->this->read);
	printf("Message reçue du processus enfant : %s\n", reponse);
	solib->free(solib, reponse);

	//test = parent->get->integer(parent->this->read);
	//printf("Message reçue du processus enfant : %d\n", test);

	close_pipe(parent->this->read, parent->this->write);*/
	solib->close(solib, EXIT_SUCCESS);
    return (0);
}


