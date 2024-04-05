/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 05:44:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>


// Fonction pour écrire des données dans un pipe
void write_data_to_pipe(int fd, void *data, size_t size) {
    if (write(fd, data, size) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour lire des données depuis un pipe
void read_data_from_pipe(int fd, void *data, size_t size) {
    if (read(fd, data, size) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

// 1 ecriture
// 0 lecture
/*
t_sofork_pipe	*new_pipe()
{
	int pipefd[2];
	t_sofork_pipe	*pipe;

	pipe = (t_sofork_pipe *)malloc(sizeof(t_sofork_pipe));
	if (pipe(pipefd) == -1)
        return (free(pipe), NULL);
	pipe->read = pipefd[0];
	pipe->write = pipefd[1];
	return (pipe);
}

int	myChild(t_solib *solib, t_sofork_child *child)
{
	(void)solib;
	(void)child;
	return (false);
}


// Fonction pour écrire des données dans un pipe
void write_data_to_pipe(int fd, void *data, size_t size) {
    if (write(fd, data, size) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour lire des données depuis un pipe
void read_data_from_pipe(int fd, void *data, size_t size) {
    if (read(fd, data, size) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

int	new_sofork_pipe(t_sofork_parent *parent, t_sofork_child *child)
{
	t_sofork_parent *parent_pipe;
	t_sofork_parent *child_pipe;

	parent_pipe = new_pipe();
	if (!parent_pipe)
		return(perror("pipex: pipe"), 1);
	child_pipe = new_pipe();
	if (!parent_pipe)
		return(perror("pipex: pipe"), 1);
	parent->this = parent_pipe;
	parent->child = child_pipe;
	child->parent = parent_pipe;
	child->this = child_pipe;
	return (0);
}

int	new_sofork_fork(t_sofork_parent *parent, t_sofork_child *child, int (*callback)(t_sofork_child *))
{
	pid_t pid;
	
	pid = fork();
    if (pid == -1)
        return(perror("pipex: fork"), 1);
	// set pid of parent and child
	if (pid == 0) // Processus enfant
	{
		child->pid->parent = getppid();
        child->pid->child = getpid();
		if (callback(child))
		{
			perror("pipex: children pid : ");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		parent->pid->parent = getpid();
        parent->pid->child = pid;
	}
	return (0);
}


t_sofork_parent	*new_fork(int (*callback)(t_sofork_child *))
{
	t_sofork_parent *parent;
	t_sofork_child *child;
	parent = (t_sofork_parent *)malloc(sizeof(t_sofork_parent));
	child = (t_sofork_child *)malloc(sizeof(t_sofork_child));

	if (new_sofork_pipe(parent, child))
		exit(EXIT_FAILURE);
	parent->send = write_data_to_pipe; // fonction pour envoyer du parent a l'enfant
	parent->get = read_data_from_pipe; // fonction pour recevoir de l'enfant au parent
	child->send = write_data_to_pipe;
	child->get = read_data_from_pipe;

	if (new_sofork_fork(parent, child, callback))
		exit(EXIT_FAILURE);
	return (parent);
}
*/

int	mychild(t_solib *solib, t_sofork_child *child)
{
	(void)solib;
	int received_num;
	char received_message[100];
	char response[] = "Salut, parent !";

	// Lecture de l'entier depuis le pipe parent vers enfant en utilisant la fonction définie
	child->get(child->this->read, &received_num, sizeof(int));
	printf("Entier reçu du processus parent : %d\n", received_num);

	// Lecture de la chaîne de caractères depuis le pipe parent vers enfant en utilisant la fonction définie
	child->get(child->this->read, received_message, sizeof(received_message));
	printf("Message reçu du processus parent : %s\n", received_message);

	// Écrire la réponse dans le pipe enfant vers parent en utilisant la fonction définie
	child->send(child->this->write, response, strlen(response) + 1);

	return (0);
}

int main() {
	t_solib	*solib;

	solib = sonew();
    int num = 42;
    char message[] = "Salut, children !";

	t_sofork_parent *parent = solib->new->fork(solib, mychild);
	// Écrire l'entier dans le pipe parent vers enfant en utilisant la fonction définie
	parent->send(parent->this->write, &num, sizeof(int));

	// Écrire la chaîne de caractères dans le pipe parent vers enfant en utilisant la fonction définie
	parent->send(parent->this->write, message, strlen(message) + 1);

	char received_response[100];
	// Lecture de la réponse depuis le pipe enfant vers parent en utilisant la fonction définie
	parent->get(parent->this->read, received_response, sizeof(received_response));
	printf("Réponse reçue du processus enfant : %s\n", received_response);

	// Fermeture des descripteurs de fichier
	close_pipe(parent->this->read, parent->this->write);
	solib->close(solib, EXIT_SUCCESS);
    return (0);
}
