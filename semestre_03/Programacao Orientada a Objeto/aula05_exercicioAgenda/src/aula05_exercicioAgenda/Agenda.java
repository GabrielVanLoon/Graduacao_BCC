package aula05_exercicioAgenda;

/**
 * Essa classe implementa as funções básicas de uma agenda de pessoas.
 * Sua implementação é estática e permite a inserção de até 10 pessoas.
 * 
 * @author Gabriel Van Loon
 *
 */

public class Agenda {
	private int 		qtd;
	private Pessoa[]	contatos;
	
	public Agenda() {
		this.qtd = 0;
		this.contatos = new Pessoa[10];
	}
	
	/**
	 * Armazena uma nova pessoa na sua agenda. Caso ela já esteja lotada, 
	 * imprime  uma mensagem de erro.
	 * @param nome
	 * @param idade
	 * @param altura
	 */
	void armazenaPessoa(String nome, int idade, float altura) {
		// Caso a agenda já esteja na capacidade máxima.
		if(this.qtd == 10) {
			System.out.println("Agenda lotada! Por favor libere espaço para uso.");
			return;
		}
		// Cadastra a pessoa e atualiza a quantidade.
		Pessoa p = new Pessoa(nome, idade, altura);
		this.contatos[this.qtd] = p;
		this.qtd += 1;
	}
	
	/**
	 * Remove a pessoa indicada pelo nome da sua agenda. Caso a pessoa
	 * não seja encontrada emite uma mensagem de erro.
	 * @param nome
	 */
	void removePessoa(String nome) {
		int pos = this.buscaPessoa(nome);
		
		// Erro: não encontrou a pessoa para remover.
		if(pos == -1) {
			System.out.println("A pessoa informada não foi encontrada na agenda!");
			return;
		}
		
		// Shiftando os proximos contatos para frente
		for(int i = pos+1; i < this.qtd; i++){
			this.contatos[i-1] = this.contatos[i];
		}
		this.qtd -= 1;
	}
	
	/**
	 * Busca uma pessoa na agenda, retornando seu indíce em caso de sucesso
	 * ou -1 caso não tenha sido possível encontrá-la.
	 * @param nome
	 * @return indíce(0 <= i < 10) ou erro(-1)
	 */
	int  buscaPessoa(String  nome) {  //  informa  em  que  posição  da  agenda  está  a pessoa
		Pessoa 	aux;
		for(int i = 0; i < this.qtd; i++) {
			aux = this.contatos[i];
			if(nome.equals(aux.getNome())) {
				return i;
			}
		}
		return -1;
	}
	
	/**
	 * Imprime na tela a posição de cada pessoa existente na agenda e,
	 * em seguida, suas informações pessoais.
	 */
	void imprimeAgenda() {  // imprime os dados de todas as pessoas da agenda
		Pessoa aux;
		for(int i = 0; i < this.qtd; i++) {
			aux = this.contatos[i];
			System.out.print( (i+1) + "º: " );
			aux.imprimirDados();
		}
	}
	
	/**
	 * Imprime os dados de uma pessoa na posição i na agenda. Caso essa posição
	 * não possua ninguém exibe uma mensagem de erro.
	 * @param i
	 */
	void  imprimePessoa(int  i) { //  imprime  os  dados  da  pessoa  que  está  na posição “i” da agenda
		int pos = i-1;
		if(pos >= this.qtd) {
			System.out.println("Não há ninguem na " + i + "ª posição.");
		} else {
			Pessoa aux = this.contatos[pos];
			aux.imprimirDados();
		}
	}
}
