package aulaxx_dicionario;

public class Dicionario<K,V> {
	
	public static int maxSize = 100;
	
	public K[] chave;
	public V[] valor;
	public int fim;
	
	@SuppressWarnings("unchecked")
	public Dicionario() {
		this.chave  = (K[]) new Object[100];
		this.valor  = (V[]) new Object[100];
		
		for(int i = 0; i < 100; i++){
			this.chave[i] = null;
			this.valor[i] = null;
		}
	}
	
	public void add(K chave, V valor){
		// Procurando lugar vago
		int i;
		for(i = 0; i < 100; i++){
			if(this.chave[i] == null && this.valor[i] == null){
				this.chave[i] = chave;
				this.valor[i] = valor;
				break;
			}
		}
	}
	
	public V get(K chave){
		for(int i = 0; i < 100; i++){
			if(this.chave[i] != null && this.chave[i] == chave){
				return this.valor[i];
			}
		}
		return null;
	}
	
	public boolean contains(K chave){
		for(int i = 0; i < 100; i++){
			if(this.chave[i] != null && this.chave[i] == chave){
				return true;
			}
		}
		return false;
	}
	
	public boolean containsValue(K chave){
		for(int i = 0; i < 100; i++){
			if(this.chave[i] != null && this.chave[i] == chave){
				return (this.valor[i] != null);
			}
		}
		return false;
	}
	

}
