package exe01_Agenda;

public class PessoaJuridica extends Pessoa{
	private String cnpj;
	private String razaoSocial;
	private String inscricaoEstadual;
	
	public PessoaJuridica(){
	
	}
	
	public PessoaJuridica(String nome, String dtNascimento, String endereco, String tel, String mail, String cnpj, String razaoSocial, String inscricao){
		super(nome, dtNascimento, endereco, tel, mail);
		this.cnpj = cnpj;
		this.razaoSocial = razaoSocial;
		this.inscricaoEstadual = inscricao;
	}

	public String getCnpj() {
		return cnpj;
	}

	public void setCnpj(String cnpj) {
		this.cnpj = cnpj;
	}

	public String getRazaoSocial() {
		return razaoSocial;
	}

	public void setRazaoSocial(String razaoSocial) {
		this.razaoSocial = razaoSocial;
	}

	public String getInscricaoEstadual() {
		return inscricaoEstadual;
	}

	public void setInscricaoEstadual(String inscricaoEstadual) {
		this.inscricaoEstadual = inscricaoEstadual;
	}
	
	@Override
	public String toString() {
		String str = "";
		str += "Nome: " + getNome() + "\tNascimento: " + getDtNascimento() + "\n";
		str += "CNPJ: " + getCnpj() + "\tRazao: " + getRazaoSocial() + "\n";
		str += "E-mail: " + getEmail() + "\tTelefone: " + getTelefone() + "\n"; 
		str += "Endereço: " + getEndereco() + "\n"; 
		return str;
	}
	
}
