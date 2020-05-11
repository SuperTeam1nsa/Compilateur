--En cours

library IEEE;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity chemindonnees is
Port (  
    CLK : in  STD_LOGIC;
    RST : in std_logic;
	AOUT  : out std_logic_vector(7 downto 0);
	BOUT  : out std_logic_vector(7 downto 0);

end chemindonnees;

architecture Behavioral of chemindonnees is

-- On ajoute les composants

component bancregistre
    Port ( A : in  STD_LOGIC_VECTOR (3 downto 0);
           B : in  STD_LOGIC_VECTOR (3 downto 0);
           addW : in  STD_LOGIC_VECTOR (3 downto 0);
           W : in  STD_LOGIC;  
           Data : in  STD_LOGIC_VECTOR (7 downto 0);
           RST : in  STD_LOGIC;  
           CLK : in  STD_LOGIC;
           QA : out  STD_LOGIC_VECTOR (7 downto 0);
           QB : out  STD_LOGIC_VECTOR (7 downto 0)
			  );
end component;

component ual
    Port ( A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           Ctrl_Alu : in  STD_LOGIC_VECTOR (2 downto 0);
           S : out  STD_LOGIC_VECTOR (7 downto 0);
           N : out  STD_LOGIC;
           O : out  STD_LOGIC;
           Z : out  STD_LOGIC;
           C : out  STD_LOGIC);
end component;

component donneesmemoire
Port (  Add : in  STD_LOGIC_VECTOR (7 downto 0);
        INS : in  STD_LOGIC_VECTOR (7 downto 0); --IN pas possible
        RW : in  STD_LOGIC; 
        RST : in  STD_LOGIC;
        CLK : in  STD_LOGIC;
        OUTS : out  STD_LOGIC_VECTOR (7 downto 0)); --OUT pas possible
end component;

component instructionsmemoire
Port ( Add : in  STD_LOGIC_VECTOR (7 downto 0);
       CLK : in  STD_LOGIC;
       OUTS : out  STD_LOGIC_VECTOR (31 downto 0)); --OUT pas possible
end component;

component pipeline1
Port (     CLK : in  STD_LOGIC;
		   OP : in  STD_LOGIC_VECTOR (7 downto 0);
           A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           C : in  STD_LOGIC_VECTOR (7 downto 0);
           OOP : out  STD_LOGIC_VECTOR (7 downto 0);
           OA : out  STD_LOGIC_VECTOR (7 downto 0);
           OB : out  STD_LOGIC_VECTOR (7 downto 0);
           OC : out  STD_LOGIC_VECTOR (7 downto 0));
end component;

--On defini les signaux
signal A_LI : std_logic_vector(7 downto 0):= (others =>'0');
signal OP_LI : std_logic_vector(7 downto 0):= (others =>'0');
signal B_LI : std_logic_vector(7 downto 0):= (others =>'0');
signal C_LI : std_logic_vector(7 downto 0):= (others =>'0');


signal A_DI : std_logic_vector(7 downto 0):= (others =>'0');
signal OP_DI : std_logic_vector(7 downto 0):= (others =>'0');
signal B_DI : std_logic_vector(7 downto 0):= (others =>'0');
signal C_DI : std_logic_vector(7 downto 0):= (others =>'0');


signal A_EXM : std_logic_vector(7 downto 0):= (others =>'0');
signal OP_EX : std_logic_vector(7 downto 0):= (others =>'0');
signal B_EX : std_logic_vector(7 downto 0):= (others =>'0');


signal A_MEM : std_logic_vector(7 downto 0):= (others =>'0');
signal OP_MEM : std_logic_vector(7 downto 0):= (others =>'0');
signal B_MEM : std_logic_vector(7 downto 0):= (others =>'0');

--Pour les signaux, j'ai mis tout 8bits 7-0. Tu es d'accord ? 

signal S : std_logic_vector(7 downto 0):= (others =>'0');
signal Ctrl_Alu : std_logic_vector(2 downto 0):= (others =>'0');
signal W : STD_LOGIC;
signal RW : STD_LOGIC;
signal QA : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal QB : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal OUTS : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal MUX : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal MUX2 : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal MUX3 : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');
signal AddMUX : STD_LOGIC_VECTOR(7 downto 0):= (others =>'0');

signal temp : std_logic_vector(31 downto 0):= (others =>'0');
	
signal IP : std_logic_vector(7 downto 0):= (others =>'0');

begin
-----------------------Instructions memoire Instanciation

instructionsmemoire_inst : instructionsmemoire PORT MAP
( Add => IP,
       CLK => CLK,
       OUTS => temp); 

-----------------------------------------------------------------------
----------------------------------LI/DI
-----------------------------------------------------------------------
pipeline1 : pipeline1 PORT MAP (     
           CLK => CLK,
	   OP => temp(31 downto 24),
           A => temp(23 downto 16),
           B => temp(15 downto 8),
           C => temp(7 downto 0),
           OOP => OP_LI,
           OA => A_LI,
           OB => B_LI,
           OC => C_LI);


-----------------------Banc de Registres Instanciation

 bancregistre_inst : bancregistre PORT MAP
         ( A => B_LI(3 downto 0),
           B => C_LI(3 downto 0),
           addW => A_MEM(3 downto 0),
           W => W,
           Data => B_MEM,
           RST => RST, 
           CLK => CLK,
           QA => QA,
           QB => QB
			  );
-----------------------------------------------------------------------
----------------------------------DI/EX
-----------------------------------------------------------------------

pipeline2 : pipeline1 PORT MAP (     
           CLK => CLK,
           OP => OP_LI,
           A => A_LI,
           B => MUX,
           C => QB,
           OOP => OP_DI,
           OA => A_DI,
           OB => B_DI,
           OC => C_DI);

-----------------------UAL Instanciation


ual_inst : ual PORT MAP (
           A => B_DI,
           B => C_DI,
           Ctrl_Alu => Ctrl_Alu,
           S => S,
           N => open,
           O => open,
           Z => open,
           C => open);

-----------------------------------------------------------------------
----------------------------------EX/MEM
-----------------------------------------------------------------------
pipeline3 : pipeline1 PORT MAP (     
           CLK => CLK,
	   OP => OP_DI,
           A => A_DI,
           B => MUX2,
           C => open,
           OOP => OP_EX,
           OA => A_EX,
           OB => B_EX,
           OC => open);

-----------------------Memoire de donnees Instanciation

donneesmemoire_inst : donneesmemoire PORT MAP
 (  Add => AddMUX;
        INS => B_EX,
        RW => RW, 
        RST => RST,
        CLK => CLK,
        OUTS => OUTS);

-----------------------------------------------------------------------
----------------------------------MEM/RE
-----------------------------------------------------------------------
pipeline4 : pipeline1 PORT MAP (     
           CLK => CLK,
	   OP => OP_EX,
           A => A_EX,
           B => MUX3,
           C => open,
           OOP => OP_MEM,
           OA => A_MEM,
           OB => B_MEM,
           OC => open);
	
-----------------------------------------------------------------------
----------------------------------Partie sensible
-----------------------------------------------------------------------

----------------------------------Operations

--On doit configurer W, RW, MUX, MUX2, MUX3, AddMUX, Ctrl_alu
	
--Ctrl_alu de l'UAL
--Ctrl_Alu <= 
	
--W du Banc de Registres
--W <=	
	
-- MUX MUX2 MUX3 et AddMUX
--MUX <=
--MUX2 <=
--MUX3 <=
--AddMUX <=
	
-- RW de Memoire de donnees
--RW <=	
----------------------------------Clock et incrementation du pointeur
process 
	begin
		wait until CLK'event and CLK = '1';
			if (RST = "0") then
				IP <= x"00";
			else
				IP <= IP+1;
			end if;
	

end Behavioral;
