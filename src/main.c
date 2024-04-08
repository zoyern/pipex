/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 21:16:11 by marvin           ###   ########.fr       */
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


int main(int argc, char **argv, char **envp) {
	t_solib	*solib;
	t_sofork_parent *parent;
	char	*reponse;

	solib = sonew(argc, argv, envp);
	reponse = solib->shell(solib, "ls -la");
	printf("--------reponse de la commande : \n%s\n--------------fin de la reponse de la commande\n", reponse);
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

	close_pipe(parent->this->read, parent->this->write);
	solib->close(solib, EXIT_SUCCESS);
    return (0);
}
