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
signal A_LI : std_logic_vector(7 downto 0);
signal OP_LI : std_logic_vector(7 downto 0);
signal B_LI : std_logic_vector(7 downto 0);
signal C_LI : std_logic_vector(7 downto 0);


signal A_DI : std_logic_vector(7 downto 0);
signal OP_DI : std_logic_vector(7 downto 0);
signal B_DI : std_logic_vector(7 downto 0);
signal C_DI : std_logic_vector(7 downto 0);


signal A_EXM : std_logic_vector(7 downto 0);
signal OP_EX : std_logic_vector(7 downto 0);
signal B_EX : std_logic_vector(7 downto 0);


signal A_MEM : std_logic_vector(7 downto 0);
signal OP_MEM : std_logic_vector(7 downto 0);
signal B_MEM : std_logic_vector(7 downto 0);


begin


end Behavioral;
