create table if not exists Funcionarios(id bigint not null primary key auto_increment, 
										nome varchar (45) not null,
                                        cargo varchar(45) not null,
                                        horario time not null,
                                        idade int not null,
                                        CPF varchar(50) not null,
                                        RG varchar (20) not null,
                                        Data_Contratacao date not null);
                                        
                                        
create table if not exists Produtos (id bigint not null primary key auto_increment,
									 nome_produto varchar(45) not null,
                                     preco float not null,
                                     validade datetime not null,
                                     frabicacao datetime not null,
                                     cod_barras varchar(45) not null,
                                     quantidade int not null);
                                     
 CREATE TABLE IF NOT EXISTS Descartes (
    id BIGINT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    QuantidadeDescarte INT NOT NULL,
    produtos_id BIGINT,
    FOREIGN KEY (produtos_id) REFERENCES produtos(id)
);

drop table descarte;
