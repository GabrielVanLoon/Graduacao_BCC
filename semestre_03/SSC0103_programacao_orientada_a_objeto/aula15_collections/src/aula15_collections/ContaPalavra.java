package aula15_collections;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;


public class ContaPalavra {
	private File   inFile;
	private Scanner scanner;
	private HashMap<String, Integer> map;
	
	public ContaPalavra(String filename) throws FileNotFoundException {
		this.map      = new HashMap<String, Integer>();
		this.inFile   = new File(filename);
		this.scanner  = new Scanner(inFile);
		scanner.useDelimiter("\\W");
	}
	
	public void criaMapa() {
		
		while(scanner.hasNext()) {
			String word = scanner.next().toLowerCase();
			
			if(map.containsKey(word)) {
				int count = map.get(word);
				map.put(word, count+1);
			} else {
				map.put(word, 0);
			}
		}
	}
	
	public void mostraMapa() {
		Set<String> keys = map.keySet();
		
		TreeSet<String> sortedKeys = new TreeSet<String>(keys);
		
		System.out.println("Mapa contém:\nChave\t\tValor");
		
		for(String key : sortedKeys) {
			System.out.printf("%-20s%10d\n", key, map.get(key));
		}
		
	}
}

