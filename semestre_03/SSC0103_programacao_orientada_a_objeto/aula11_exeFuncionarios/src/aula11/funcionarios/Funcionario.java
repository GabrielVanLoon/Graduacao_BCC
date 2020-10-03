package aula11.funcionarios;

/**
 * Classe abstrata que contém todos so atributos e métodos comuns aos funcionários de uma loja.
 * @author Gabriel Van Loon 10391607
 *
 */
public abstract class Funcionario {
	
	private String nome;
	private String cpf;
	private double salarioBase;
	
	/**
	 * Construtor padrão de um funcionário que também verifica se os parâmetros recebidos
	 * pelo usuário são válidos. Caso não sejam emite um IllegalArgumentException;
	 * @param nome
	 * @param cpf
	 * @param salarioBase
	 * @throws IllegalAccessException
	 */
	public Funcionario(String nome, String cpf, double salarioBase) throws IllegalAccessException {
		if(!Funcionario.verificaCPF(cpf))
			throw new IllegalArgumentException("Erro, o CPF enviado é inválido!");
		
		if(salarioBase <= 0)
			throw new IllegalArgumentException("Erro, valor de salário base inválido!");
		
		this.nome = nome;
		this.cpf  = cpf;
		this.salarioBase = salarioBase;	
	}
	
	/**
	 * Função abstrata que irá retornar o salário de um funcionário.
	 * Esse valor é influenciado pelo cargo/classe do funcionário e seu salário base.
	 * @return
	 */
	public abstract double calculaSalario();
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getCpf() {
		return cpf;
	}

	public void setCpf(String cpf) {
		this.cpf = cpf;
	}

	public double getSalarioBase() {
		return salarioBase;
	}

	public void setSalarioBase(double salarioBase) {
		this.salarioBase = salarioBase;
	}
	
	/**
	 * Função estática auxiliar da classe Funcionario. Dada uma string de cpf, 
	 * retorna se a mesma é válida ou não.
	 * Obs. A função pode receber o cpf com pontuação, pois o mesmo faz o tratamento
	 * de caracteres não numéricos antes da validação.
	 * @param cpf
	 * @return true se CPF for válido.
	 */
	public static boolean verificaCPF(String cpf) {
		String cpfLimpo = cpf.replaceAll("[^0-9]", "");
		int[] digito = new int[9];
		int[] valid  = new int[2];
		
		// O cpf não tem números suficientes para ser válido
		if(cpfLimpo.length() != 11) 
			return false;
		
		// Lendo os valores em inteiro
			for(int i = 0; i < 9; i++) {
				char c = cpfLimpo.charAt(i);
				digito[i] = Character.getNumericValue(c);
			} 
			
			valid[0] = Character.getNumericValue(cpfLimpo.charAt(9));
			valid[1] = Character.getNumericValue(cpfLimpo.charAt(10));
		
		// Verificando se todos os digitos são iguais
			boolean todosIguais = true;
			for(int i = 1; i < 9; i++) {
				if(digito[i-1] != digito[i])
					todosIguais = false;
			}
			
			if(todosIguais)
				return false;
		
		// Validando o primeiro digito
			int mult = 0;
			
			int j = 0;
			for(int i = 10; i >= 2; i--)
				mult += digito[j++] * i;
			
			int resto = (mult * 10) % 11;
			resto = resto % 10;
			
			if(resto != valid[0])
				return false;
		
		// Validando o segundo digito
			mult = 0;
			j = 0;
			for(int i = 11; i >= 3; i--)
				mult += digito[j++] * i;
			mult += valid[0] * 2;
			
			resto = (mult * 10) % 11;
			resto = resto % 10;
			
			if(resto != valid[1])
				return false;
		
		return true;
	}
	
}































