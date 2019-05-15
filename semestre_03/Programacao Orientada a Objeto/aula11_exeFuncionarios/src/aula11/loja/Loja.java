package aula11.loja;

import java.util.ArrayList;
import aula11.funcionarios.*;

/**
 * Abstrai uma loja e insere funcionários nela.
 * @author Gabriel Van Loon 10391607
 *
 */
public class Loja {
	
	private ArrayList<Funcionario> funcionarios;
	
	/**
	 * Construtor da classe Loja
	 */
	public Loja() {
		this.funcionarios = new ArrayList<Funcionario>();
	}
	
	/**
	 * Insere um funcionário no array de funcionários
	 * @param f
	 */
	public void cadastrarFuncionario(Funcionario f) {
		if(f != null)
			funcionarios.add(f);
	}
	
	/**
	 * Exibe a folha salarial de todos os funcionários e também a soma total
	 * de todos os salários.
	 */
	public void mostrarFolhaSalarial() {
		double total = 0;
		
		System.out.println("\t# FOLHA SALARIAL DE FUNCIONÁRIOS:# ");
		for(Funcionario f : funcionarios) {
			System.out.println(f);
			total += f.calculaSalario();
		}
		System.out.println("\t# TOTAL A PAGAR: R$"+ String.format("%.2f", total) +"# ");
	}
	
	public static void main(String[] args) {
		
		Loja lj = new Loja();
		
		Gerente[]    g = new Gerente[2];
		Assistente[] a = new Assistente[2];
		Vendedor[]   v = new Vendedor[2];
		
		// Inserindo os Gerentes
		try {
			g[0] = new Gerente("Gabriel", "111.111.111-11", 1200.30);
			lj.cadastrarFuncionario(g[0]);
			
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		try {
			g[1] = new Gerente("Tamires", "108.231.911-25", 1590.30);
			lj.cadastrarFuncionario(g[1]);
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		// Inserindo os Assistentes
		try {
			a[0] = new Assistente("Thabata", "022.311.518-55", 1000.90);
			lj.cadastrarFuncionario(a[0]);
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		try {
			a[1] = new Assistente("Roberval", "548.255.712-04", -1100.00);
			lj.cadastrarFuncionario(a[1]);
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		// Inserindo os vendedores
		try {
			v[0] = new Vendedor("Matt Smith", "351.726.407-54", 800.00, 300.00);
			lj.cadastrarFuncionario(v[0]);
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		try {
			v[1] = new Vendedor("Aline", "234.967.218-77", 800.00, 250.00);
			lj.cadastrarFuncionario(v[1]);
		} catch(Exception e) {
			System.out.println("\tOcorreu um erro ao cadastrar o funcionário.");
			System.out.println("\tCausa: " + e.getMessage());
			System.out.println();
		}
		
		
		lj.mostrarFolhaSalarial();
		
	}
	
	
	
}
