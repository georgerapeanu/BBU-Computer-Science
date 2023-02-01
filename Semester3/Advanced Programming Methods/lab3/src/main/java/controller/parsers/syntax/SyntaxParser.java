package controller.parsers.syntax;

import controller.parsers.expressions.ExpressionParser;
import controller.parsers.expressions.exceptions.InvalidExpressionAppException;
import controller.parsers.syntax.exceptions.SyntaxAppException;
import model.abstract_data_types.generic_list.GenericList;
import model.abstract_data_types.generic_list.IGenericList;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.statements.*;
import model.values.types.*;
import utils.RefInt;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
    TYPE = IntegerType|BooleanType
    NAME="([a-zA-Z_])+[a-zA-Z0-9_]*"
    VariableDeclarationStatement = "TYPE NAME"
    AssignmentStatement = "NAME=Expression"
    IfStatement = "If Expression Then Statement1 else Statement2"
    PrintStatement = "print(Expression)"
    NoOperationStatement = ""
    CompositeStatement = "Statement1;Statement2"
    Statement = {Statement}
 */

public class SyntaxParser {
    private static IType[] types = {new IntegerType(), new BooleanType(), new StringType()};
    private static Character[] whiteSpace = {' ', '\t', '\n', '\r'};
    private static Pattern namePattern = Pattern.compile("^(([a-zA-Z_])+[a-zA-Z0-9_]*)");

    private static void skipWhiteSpace(String string, RefInt position) {
        while(position.getValue() < string.length() && Arrays.asList(whiteSpace).contains(string.charAt(position.getValue()))){
            position.increase(1);
        }
    }
    private static IType extractType(String string, RefInt position) throws SyntaxAppException {
        RefInt tmpPosition = new RefInt(position.getValue());
        int refCount = 0;
        while(true){
            skipWhiteSpace(string, tmpPosition);
            if(tmpPosition.getValue() >= string.length()){
                throw new SyntaxAppException("No type present");
            }
            if(tmpPosition.getValue() + "RefType".length() - 1 >= string.length() ||
                    !string.substring(tmpPosition.getValue(), tmpPosition.getValue() + "RefType".length()).equals("RefType")){
                break;
            }
            tmpPosition.increase("RefType".length());
            refCount++;
        }
        for(IType type : types){
            if(tmpPosition.getValue() + type.toString().length() <= string.length() && string.substring(tmpPosition.getValue(), tmpPosition.getValue() + type.toString().length()).equals(type.toString())) {
                tmpPosition.increase(type.toString().length());
                position.setValue(tmpPosition.getValue());
                IType answer = type;
                while(refCount > 0){
                    answer = new RefType(answer);
                    refCount--;
                }
                return answer;
            }
        }
        throw new SyntaxAppException("No type present");
    }

    private static String extractName(String string, RefInt position) throws SyntaxAppException {
        Matcher matcher = namePattern.matcher(string.substring(position.getValue()));
        if(!matcher.find()){
            throw new SyntaxAppException("No name found");
        }
        String answer = matcher.group(1);
        position.increase(matcher.group(0).length());
        return answer;
    }


    private static IStatement parseAssignment(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        String name = extractName(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != '=') {
            throw new SyntaxAppException("Invalid assignment");
        }
        position.increase(1);
        skipWhiteSpace(string, position);
        return new AssignmentStatement(name, ExpressionParser.parseAtPosition(string, position));
    }

    private static IStatement parseVariableDeclaration(String string, RefInt position) throws SyntaxAppException {
        skipWhiteSpace(string, position);
        IType type = extractType(string, position);
        skipWhiteSpace(string, position);
        String name = extractName(string, position);
        return new VariableDeclarationStatement(name, type);
    }



    private static IStatement parseNew(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 3 >= string.length() || !string.substring(position.getValue(), position.getValue() + 4).equals("new(")){
            throw new SyntaxAppException("Invalid new statement");
        }
        position.increase(4);
        String name = extractName(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ','){
            throw new SyntaxAppException("Invalid new statement");
        }
        position.increase(1);
        skipWhiteSpace(string, position);
        IExpression expr = ExpressionParser.parseAtPosition(string, position);

        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ')') {
            throw new SyntaxAppException("Invalid new statement");
        }
        position.increase(1);
        return new NewStatement(name, expr);
    }

    private static IStatement parseWriteHeap(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 9 >= string.length() || !string.substring(position.getValue(), position.getValue() + 10).equals("writeHeap(")){
            throw new SyntaxAppException("Invalid writeHeap statement");
        }
        position.increase(10);

        skipWhiteSpace(string, position);
        IExpression addressExpression = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ','){
            throw new SyntaxAppException("Invalid new statement");
        }
        position.increase(1);
        skipWhiteSpace(string, position);

        IExpression valueExpression = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ')') {
            throw new SyntaxAppException("Invalid writeHeap statement");
        }
        position.increase(1);
        return new WriteHeapStatement(addressExpression, valueExpression);
    }

    private static IStatement parseReadHeap(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 8 >= string.length() || !string.substring(position.getValue(), position.getValue() + 9).equals("readHeap(")){
            throw new SyntaxAppException("Invalid readHeap statement");
        }
        return new ReadHeapStatement(ExpressionParser.parseAtPosition(string, position));
    }

    private static IStatement parsePrint(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 5 >= string.length() || !string.substring(position.getValue(), position.getValue() + 6).equals("print(")){
            throw new SyntaxAppException("Invalid print statement");
        }
        position.increase(5);
        return new PrintStatement(ExpressionParser.parseAtPosition(string, position));
    }

    private static IStatement parseFork(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 4 >= string.length() || !string.substring(position.getValue(), position.getValue() + 5).equals("fork(")){
            throw new SyntaxAppException("Invalid fork statement");
        }
        position.increase(5);
        skipWhiteSpace(string, position);
        IStatement innerStatement = SyntaxParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ')'){
            throw new SyntaxAppException("Invalid fork statement");
        }
        position.increase(1);
        return new ForkStatement(innerStatement);
    }
    private static IStatement parseSwitch(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 6 >= string.length() || !string.substring(position.getValue(), position.getValue() + 7).equals("switch(")){
            throw new SyntaxAppException("Invalid switch statement");
        }
        position.increase(6);
        skipWhiteSpace(string, position);

        IExpression expression = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        IGenericList<IExpression> expressions = new GenericList<>();
        IGenericList<IStatement> statements = new GenericList<>();



        while(true){
            skipWhiteSpace(string, position);
            if(position.getValue() >= string.length()){
                throw new SyntaxAppException("Unexpected end");
            }
            if(string.charAt(position.getValue()) == ';'){
                break;
            }
            if(string.charAt(position.getValue()) != '('){
                throw new SyntaxAppException("Invalid switch clause body");
            }
            position.increase(1);
            skipWhiteSpace(string, position);
            if(position.getValue() + 6 < string.length() && string.substring(position.getValue(), position.getValue() + 7).equals("default")) {
               position.increase(7);
            } else {
                if(position.getValue() + 3 >= string.length()){
                    throw new SyntaxAppException("Unexpected end");
                }
                if(!string.substring(position.getValue(), position.getValue() + 4).equals("case")){
                    throw new SyntaxAppException("Invalid switch clause body expected case");
                }
                position.increase(4);;
                expressions.addToEnd(ExpressionParser.parseAtPosition(string, position));
            }
            skipWhiteSpace(string, position);
            if(position.getValue() >= string.length()){
                throw new SyntaxAppException("Unexpected end");
            }
            if(string.charAt(position.getValue()) != ':'){
                throw new SyntaxAppException("Invalid switch clause body: missing :");
            }
            position.increase(1);
            skipWhiteSpace(string, position);
            statements.addToEnd(SyntaxParser.parseAtPosition(string, position));
            if(position.getValue() >= string.length()){
                throw new SyntaxAppException("Unexpected end");
            }
            if(string.charAt(position.getValue()) != ')'){
                throw new SyntaxAppException("Invalid switch clause body: missing :");
            }
            position.increase(1);
        }

        return new SwitchStatement(expression, expressions, statements);
    }

    private static IStatement parseIf(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 2 >= string.length()){
            throw new SyntaxAppException("Invalid if syntax");
        }
        String ifBegin = string.substring(position.getValue(), position.getValue() + 3);
        if(!(ifBegin.startsWith("if ") || ifBegin.startsWith("if("))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(2);
        IExpression cond = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        if(position.getValue() + 4 >= string.length()){
            throw new SyntaxAppException("Invalid if syntax");
        }
        String thenBegin = string.substring(position.getValue(), position.getValue() + 5);
        if(!(thenBegin.startsWith("then ") || thenBegin.startsWith("then{"))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(4);
        IStatement first = parseNonComposite(string, position);
        skipWhiteSpace(string, position);

        if(position.getValue() + 4 >= string.length()){
            throw new SyntaxAppException("Invalid if syntax");
        }
        String elseBegin = string.substring(position.getValue(), position.getValue() + 5);
        if(!(elseBegin.startsWith("else ") || elseBegin.startsWith("else{"))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(4);
        IStatement second = parseNonComposite(string, position);
        skipWhiteSpace(string, position);

        return new IfStatement(cond, first, second);
    }

    private static IStatement parseWhile(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 5 >= string.length()){
            throw new SyntaxAppException("Invalid while syntax");
        }
        String ifBegin = string.substring(position.getValue(), position.getValue() + 6);
        if(!(ifBegin.startsWith("while ") || ifBegin.startsWith("while("))){
            throw new SyntaxAppException("Invalid while syntax");
        }

        position.increase(5);
        skipWhiteSpace(string, position);
        IExpression condition = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        IStatement statement = parseNonComposite(string, position);

        return new WhileStatement(condition, statement);
    }

    private static IStatement parseNoOperation(String string, RefInt position) throws SyntaxAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ';'){
            throw new SyntaxAppException("Invalid NOP statement");
        }
        return new NoOperationStatement();
    }

    private static IStatement parseOpenRFile(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 9 >= string.length() || !string.substring(position.getValue(), position.getValue() + 10).equals("openRFile(")){
            throw new SyntaxAppException("Invalid openRFile statement");
        }
        position.increase(9);
        return new OpenFileStatement(ExpressionParser.parseAtPosition(string, position));
    }

    private static IStatement parseCloseRFile(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 10 >= string.length() || !string.substring(position.getValue(), position.getValue() + 11).equals("closeRFile(")){
            throw new SyntaxAppException("Invalid closeRFile statement");
        }
        position.increase(10);
        return new CloseFileStatement(ExpressionParser.parseAtPosition(string, position));
    }

    private static IStatement parseReadFile(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 8 >= string.length() || !string.substring(position.getValue(), position.getValue() + 9).equals("readFile(")){
            throw new SyntaxAppException("Invalid readFile statement");
        }
        position.increase(9);
        IExpression expression = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ','){
            throw new SyntaxAppException("Invalid readFile statement");
        }
        position.increase(1);
        skipWhiteSpace(string, position);
        String name = extractName(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ')'){
            throw new SyntaxAppException("Invalid readFile statement");
        }
        position.increase(1);
        return new ReadFileStatement(expression, name);
    }

    private static IStatement parseCreateSemaphore(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 15 >= string.length() || !string.substring(position.getValue(), position.getValue() + 16).equals("createSemaphore(")){
            throw new SyntaxAppException("Invalid createSemaphore statement");
        }
        position.increase(16);

        String name = extractName(string, position);
        skipWhiteSpace(string, position);

        if(string.length() <= position.getValue() || string.charAt(position.getValue()) != ','){
            throw new SyntaxAppException("Expected , in createsemaphore");
        }
        position.increase(1);
        IExpression expression = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);
        if(string.length() <= position.getValue() || string.charAt(position.getValue()) != ')'){
            throw new SyntaxAppException("Expected ) in createsemaphore");
        }
        position.increase(1);
        return new CreateSemaphoreStatement(name, expression);
    }

    private static IStatement parseAcquire(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 7 >= string.length() || !string.substring(position.getValue(), position.getValue() + 8).equals("acquire(")){
            throw new SyntaxAppException("Invalid acquire statement");
        }
        position.increase(8);

        String name = extractName(string, position);
        skipWhiteSpace(string, position);

        if(string.length() <= position.getValue() || string.charAt(position.getValue()) != ')'){
            throw new SyntaxAppException("Expected ) in acquire");
        }
        position.increase(1);
        return new AcquireStatement(name);
    }

    private static IStatement parseRelease(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 7 >= string.length() || !string.substring(position.getValue(), position.getValue() + 8).equals("release(")){
            throw new SyntaxAppException("Invalid release statement");
        }
        position.increase(8);

        String name = extractName(string, position);
        skipWhiteSpace(string, position);

        if(string.length() <= position.getValue() || string.charAt(position.getValue()) != ')'){
            throw new SyntaxAppException("Expected ) in acquire");
        }
        position.increase(1);
        return new ReleaseStatement(name);
    }

    private static IStatement parseNonComposite(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length()){
            return null;
        }
        if(string.charAt(position.getValue()) == '{') {
            position.increase(1);
            IStatement statement = parseAtPosition(string, position);
            if(string.charAt(position.getValue()) != '}'){
                throw new SyntaxAppException("Invalid syntax");
            }
            position.increase(1);
            return statement;
        }
        if (string.charAt(position.getValue()) == '}'){
            return null;
        }
        if(string.charAt(position.getValue()) == ';'){
            return parseNoOperation(string, position);
        }
        if(position.getValue() + 4 < string.length() && string.substring(position.getValue(), position.getValue() + 5).equals("print")){
            return parsePrint(string, position);
        }
        if(position.getValue() + 8 < string.length() && string.substring(position.getValue(), position.getValue() + 9).equals("openRFile")){
            return parseOpenRFile(string, position);
        }
        if(position.getValue() + 9 < string.length() && string.substring(position.getValue(), position.getValue() + 10).equals("closeRFile")){
            return parseCloseRFile(string, position);
        }
        if(position.getValue() + 7 < string.length() && string.substring(position.getValue(), position.getValue() + 8).equals("readFile")){
            return parseReadFile(string, position);
        }
        if(position.getValue() + 2 < string.length() && string.substring(position.getValue(), position.getValue() + 2).equals("if")){
            return parseIf(string, position);
        }
        if(position.getValue() + 5 < string.length() && string.substring(position.getValue(), position.getValue() + 5).equals("while")){
            return parseWhile(string, position);
        }
        if(position.getValue() + 2 < string.length() && string.substring(position.getValue(), position.getValue() + 3).equals("new")){
            return parseNew(string, position);
        }
        if(position.getValue() + 7 < string.length() && string.substring(position.getValue(), position.getValue() + 8).equals("readHeap")){
            return parseReadHeap(string, position);
        }
        if(position.getValue() + 8 < string.length() && string.substring(position.getValue(), position.getValue() + 9).equals("writeHeap")){
            return parseWriteHeap(string, position);
        }
        if(position.getValue() + 3 < string.length() && string.substring(position.getValue(), position.getValue() + 4).equals("fork")){
            return parseFork(string, position);
        }
        if(position.getValue() + 5 < string.length() && string.substring(position.getValue(), position.getValue() + 6).equals("switch")){
            return parseSwitch(string, position);
        }
        if(position.getValue() + 14 < string.length() && string.substring(position.getValue(), position.getValue() + 15).equals("createSemaphore")){
            return parseCreateSemaphore(string, position);
        }
        if(position.getValue() + 6 < string.length() && string.substring(position.getValue(), position.getValue() + 7).equals("acquire")){
            return parseAcquire(string, position);
        }
        if(position.getValue() + 6 < string.length() && string.substring(position.getValue(), position.getValue() + 7).equals("release")){
            return parseRelease(string, position);
        }
        int pos = position.getValue();
        boolean hasEqual = false;
        while(! hasEqual && pos < string.length() && string.charAt(pos) != ';'){
            hasEqual = (string.charAt(pos) == '=');
            pos++;
        }
        if(hasEqual){
            return parseAssignment(string, position);
        }
        return parseVariableDeclaration(string, position);
    }



    private static IStatement parseAtPosition(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length()){
            return null;
        }
        if (position.getValue() < string.length() && (string.charAt(position.getValue()) == '}' || string.charAt(position.getValue()) == ')')){
            return null;
        }

        IStatement currentStatement = parseNonComposite(string, position);

        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ';') {
            throw new SyntaxAppException("Missing ;");
        }
        position.increase(1);
        IStatement nextStatement = parseAtPosition(string, position);
        if(nextStatement == null){
            return currentStatement;
        }
        currentStatement = new CompositeStatement(currentStatement, nextStatement);

        return currentStatement;
    }

    public static IStatement parse(String string) throws SyntaxAppException, InvalidExpressionAppException {
        return parseAtPosition(string, new RefInt(0));
    }
}
