package aula11.funcionarios;


/**
 * Classe que representa um Vendedor e implementa os métodos abstratos definidos na classe Funcionário.
 * @author Gabriel Van Loon 10391607
 *
 */
public class Vendedor extends Funcionario {
	
	private double comissao;
	
	/**
	 * O Vendedor possui os mesmos atributos que um Funcionário comum + comissao.
	 * @param nome
	 * @param cpf
	 * @param salarioBase
	 * @param comissao
	 * @throws IllegalAccessException
	 */
	public Vendedor(String nome, String cpf, double salarioBase, double comissao) throws IllegalAccessException {
		super(nome, cpf, salarioBase);
		
		if(comissao <= 0)
			throw new IllegalArgumentException("Erro, valor de comissão inválido!");
		
		this.setComissao(comissao);
	}
	
	
	/**
	 * O salário de um gerente é uma vez seu salário base + sua comissão.
	 * @return salario
	 */
	@Override
	public double calculaSalario() {
		return getSalarioBase() + getComissao();
	}

	public double getComissao() {
		return comissao;
	}

	public void setComissao(double comissao) {
		this.comissao = comissao;
	}
	
	@Override
	public String toString() {
		String str = "";
		
		str += "\tNome:" + this.getNome() + "\n";
		str += "\tCargo: Vendedor\n";
		str += "\tCPF:" + this.getCpf() + "\n";
		str += "\tSalário Base: R$" + String.format("%.2f",  this.getSalarioBase()) + "\n";
		str += "\tComissão: R$" + String.format("%.2f", this.getComissao()) + "\n";
		
		return str;
	}
	
}
