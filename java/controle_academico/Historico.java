/*
** Classe Historico - implementa um objeto Historico
** acessado pelo objeto Aluno e que esta associado
** a varios objetos DisciplinaAluno. O objeto possui 
** um Array de DisciplinaAluno hist, um construtor e os 
** metodos MatricularDisciplina, AtualizarHistorico
** e ImprimirHistorico.
*/

import java.util.ArrayList;
import java.util.Arrays;

public class Historico{
    ArrayList <DisciplinaAluno> hist;

    public Historico(){
        hist = new ArrayList <DisciplinaAluno>();
    }

    void MatricularDisciplina(DisciplinaCoord d){
        DisciplinaAluno d1 = new DisciplinaAluno(d.nome);
        hist.add(d1);
    }

    void AtualizarHistorico(String nome, double nota){
        for(DisciplinaAluno d: hist){
            if(d.nome == nome){
                d.AtualizarDisciplina(nota);
                break;
            }
        }
    }

    void ImprimirHistorico(){
        System.out.println("Historico do aluno: ");
        for(DisciplinaAluno d: hist){
            d.ImprimirDisciplina();
        }
    }
}