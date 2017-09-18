/*
** Classe GradeHoraria - implementa um objeto Grade
** Horaria acessado pela Coordenacao e que esta
** associado a varios objetos DisciplinaCoord. O objeto
** possui um Array grade de DisciplinaCoord e uma variavel
** versao, um construtor e os metodos CadastrarDisciplina
** ImprimirGrade, RemoverDisciplina e BuscarDisciplina.
*/

import javax.swing.*;
import java.util.ArrayList;
import java.util.Arrays;

public class GradeHoraria{
    ArrayList <DisciplinaCoord> grade;
    int versao;

    public GradeHoraria(int versao){
        this.versao = versao;
        grade = new ArrayList <DisciplinaCoord> ();
    }

    void CadastrarDisciplina(){
        DisciplinaCoord d;
        String nome, abr, cod, und;
        int hp, ht;
        nome = JOptionPane.showInputDialog("Digite o nome da disciplina: ");
        und = JOptionPane.showInputDialog("Digite a unidade: ");
        hp = Integer.parseInt(JOptionPane.showInputDialog("Horas praticas: "));
        ht = Integer.parseInt(JOptionPane.showInputDialog("Horas teoricas: "));
        d = new DisciplinaCoord(nome, und, hp, ht);
        grade.add(d);
    }

    void ImprimirGrade(){
        for(DisciplinaCoord d: grade){
            d.ImprimirDisciplina();
            System.out.println("");
        }
    }

    void RemoverDisciplina(){
        String nome;
        nome = JOptionPane.showInputDialog("Digite o nome da disciplina que quer remover: ");
        for(DisciplinaCoord d: this.grade){
            if(nome.equals(d.nome)){
                this.grade.remove(d);
            }
        }
    }

    DisciplinaCoord BuscarDisciplina(String nome){
        for(DisciplinaCoord d: this.grade){
            if(nome.equals(d.nome)){
                return d;
            }
        }
        return null;
    }

}