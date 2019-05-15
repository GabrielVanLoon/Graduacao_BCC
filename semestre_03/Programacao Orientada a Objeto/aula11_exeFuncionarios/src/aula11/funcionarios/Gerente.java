package aula11.funcionarios;

/**
 * Classe que representa um Gerente e implementa os métodos abstratos definidos na classe Funcionário.
 * @author Gabriel Van Loon 10391607
 *
 */
public class Gerente extends Funcionario{
	
	/**
	 * Construtor do gerente.
	 * @param nome
	 * @param cpf
	 * @param salarioBase
	 * @throws IllegalAccessException
	 */
	public Gerente(String nome, String cpf, double salarioBase) throws IllegalAccessException {
		super(nome, cpf, salarioBase);
	}
	
	/**
	 * O salário de um gerente é duas vezes seu salário base.
	 * @return salario
	 */
	@Override
	public double calculaSalario() {
		return (2.0 * getSalarioBase());
	}
	
	@Override
	public String toString() {
		String str = "";
		
		str += "\tNome:" + this.getNome() + "\n";
		str += "\tCargo: Gerente\n";
		str += "\tCPF:" + this.getCpf() + "\n";
		str += "\tSalário Base: R$" + String.format("%.2f",  this.getSalarioBase()) + "\n";
		
		return str;
	}

}
