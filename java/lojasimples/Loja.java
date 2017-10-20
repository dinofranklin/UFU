package loja;

import java.util.ArrayList;

public class Loja {
    private ArrayList <Produto> estoque;
    
    public Loja(){
        estoque = new ArrayList <Produto> ();
    }
    
    public void adicionarProduto(String nome, int qtd, double preco){
        Produto p = new Produto(nome, qtd, preco);
        estoque.add(p);
    }
    
    public void solicitarVenda(String x, int n){
        for(Produto p: estoque){
            if(x.equals(p.retornaNome())){
                if(n <= p.retornaQuantidade()){
                    p.venderProduto(n);
                    System.out.println("Vendidos " + n + " " + p.retornaNome());
                    System.out.println("Quantidade em estoque " + p.retornaQuantidade());
                }
                else{
                    System.out.println("Quantidade desejada maior do que a em estoque");
                }
                return;
            }
        }
        System.out.println("Produto não encontrado no estoque");
    }
    
    public void reporEstoque(String x, int n){
        for(Produto p: estoque){
            if(x.equals(p.retornaNome())){
                p.reporProduto(n);
                System.out.println("Repostos " + n + " " + p.retornaNome());
                System.out.println("Quantidade em estoque " + p.retornaQuantidade());
                return;
            }
        }
        System.out.println("Impossivel repor, item nao esta no estoque");
    }
    
    public int solicitaQuantidade(String x){
        for(Produto p: estoque){
            if(x.equals(p.retornaNome())){
                return p.retornaQuantidade();
            }
        }
        return 0;
    }
    
    public void imprimeQuantidade(){
        for(Produto p: estoque){
            System.out.println(p.retornaNome() + " = " + p.retornaQuantidade());
        }
    }
    
    public void imprimePrecos(){
        for(Produto p: estoque){
            System.out.println(p.retornaNome() + " = R$" + p.retornaPreco());
        }
    }
}
