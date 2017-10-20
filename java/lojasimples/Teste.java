package loja;

public class Teste {
    public static void main(String args[]){
        Loja mercado = new Loja();
        
        mercado.adicionarProduto("Bola", 20, 25.0);
        mercado.adicionarProduto("Tenis", 10, 100.0);
        
        mercado.solicitarVenda("Bola", 10);
        mercado.solicitarVenda("Tenis", 3);
        
        mercado.reporEstoque("Bola", 5);
        
        mercado.imprimeQuantidade();
    }
}