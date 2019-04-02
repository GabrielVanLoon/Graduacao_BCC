package exe01_Agenda;

public class PessoaFisica extends Pessoa {
	private String cpf;
	private String estadoCivil;
	
	public PessoaFisica(){
	}
	
	public PessoaFisica(String nome, String dtNascimento, String endereco, String tel, String mail, String cpf, String estadoCivil){
		super(nome, dtNascimento, endereco, tel, mail);
		this.cpf = cpf;
		this.estadoCivil = estadoCivil;
	}
	
	public String getCpf() {
		return cpf;
	}
	
	public void setCpf(String cpf) {
		this.cpf = cpf;
	}
	
	public String getEstadoCivil() {
		return estadoCivil;
	}
	
	public void setEstadoCivil(String estadoCivil) {
		this.estadoCivil = estadoCivil;
	}
	
	@Override
	public String toString() {
		String str = "";
		str += "Nome: " + getNome() + "\tNascimento: " + getDtNascimento() + "\n";
		str += "CPF: " + getCpf() + "\tEstadoCivil: " + getEstadoCivil() + "\n";
		str += "E-mail: " + getEmail() + "\tTelefone: " + getTelefone() + "\n"; 
		str += "Endereço: " + getEndereco() + "\n"; 
		return str;
	}
}
