package aula11.funcionarios;

/**
 * Classe que representa um Assistente e implementa os métodos abstratos definidos na classe Funcionário.
 * @author Gabriel Van Loon 10391607
 *
 */
public class Assistente extends Funcionario {
	
	/**
	 * Construtor do Assistente.
	 * @param nome
	 * @param cpf
	 * @param salarioBase
	 * @throws IllegalAccessException
	 */
	public Assistente(String nome, String cpf, double salarioBase) throws IllegalAccessException {
		super(nome, cpf, salarioBase);
	}
	
	
	/**
	 * O salário de um gerente é uma vez seu salário base.
	 * @return salario
	 */
	@Override
	public double calculaSalario() {
		return (1.0 * getSalarioBase());
	}
	
	@Override
	public String toString() {
		String str = "";
		
		str += "\tNome:" + this.getNome() + "\n";
		str += "\tCargo: Assistente\n";
		str += "\tCPF:" + this.getCpf() + "\n";
		str += "\tSalário Base: R$" + String.format("%.2f",  this.getSalarioBase()) + "\n";
		
		return str;
	}
}
