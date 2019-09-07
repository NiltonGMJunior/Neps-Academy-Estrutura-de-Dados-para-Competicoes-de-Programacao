#include <iostream>
#include <vector>

// Define o tipo de dado da lista ligada e seu alias.
#define LinkedListNodeType unsigned int
typedef LinkedListNodeType t_node;

// Define a estrutura do nó da lista ligada.
struct LinkedListNode
{
    t_node data;
    LinkedListNode *next_node;
};

// Define o alias da estrutura do nó da lista ligada.
typedef LinkedListNode node;

// Método para criação de um nó.
node *createNode(const t_node data)
{
    node *new_node = new node;
    if (!new_node)
    {
        std::cout << "Falha ao alocar memória. Encerrando o programa.\n";
        exit(-1);
    }
    
    new_node->data = data;
    new_node->next_node = nullptr;

    return new_node;
}

// Método de inserção de um nó numa lista ligada.
node *insertLast(node *head, node *new_node)
{
    if (!head)
        head = new_node;
    else
    {
        node *current_node = head;
        while (current_node->next_node)
            current_node = current_node->next_node;
        current_node->next_node = new_node;
    }

    return head;
}

// Método para remoção de nós da fila. Assume que os nós possuem dados distintos.
node *removeNode(node *head, t_node data)
{
    if (head)
    {
        if (head->data == data)
        {
            node* new_head = head->next_node;
            free(head);
            return new_head;
        }

        node *previous_node = head;
        node *current_node = head->next_node;
        while (current_node)
        {
            if (current_node->data == data)
            {
                previous_node->next_node = current_node->next_node;
                free(current_node);
                return head;
            }
            previous_node = current_node;
            current_node = current_node->next_node;
        }
    }

    return head;
}

// Imprime os dados de todos os nós na lista separados por um espaço.
void printList(node *head)
{
    node *current_node = head;
    while (current_node)
    {
        std::cout << current_node->data << ' ';
        current_node = current_node->next_node;
    }
}

// Libera a memória dos nós na lista.
void freeList(node *head)
{
    node *current_node = head;
    while(head)
    {
        head = head->next_node;
        free(current_node);
        current_node = head;
    }
}

int main(int argc, char const *argv[])
{
    // Lê o número n de pessoas inicialmente na fila (1 <= n  <= 50000)
    unsigned short int n;
    std::cin >> n;

    // Inicializa uma nova lista ligada com a fila e insere as pessoas na fila.
    node *fila = nullptr;
    node *pessoa = nullptr;
    unsigned int id;
    while(n--)
    {
        std::cin >> id;
        pessoa = createNode(id);
        fila = insertLast(fila, pessoa);
    }

    // Lê o número m de pessoas que sairam da fila (1 <= m <= 50000, m < n). Remova as pessoas da fila.
    unsigned short int m;
    std::cin >> m;
    while(m--)
    {
        std::cin >> id;
        fila = removeNode(fila, id);
    }

    // Imprime a fila.
    printList(fila);

    // Limpa a fila.
    freeList(fila);

    return 0;
}