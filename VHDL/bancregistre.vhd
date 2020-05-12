--ERREURn probleme avec les Librairies.......

library IEEE;
--use IEEE.STD_LOGIC_ARITH.ALL;
--use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;



entity bancregistre is
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
end bancregistre;

architecture Behavioral of bancregistre is

type registreTableau is array (integer range 255 downto 0) of STD_LOGIC_VECTOR(7 downto 0);
signal registr : registreTableau; --Attention on peut pas utiliser registre sinon error

begin
--Partie Asynchrone
--@A et @B permettent de lire deux registres simultanément.


--https://www.xilinx.com/support/answers/45213.html
--ATTENTION Si écriture et lecture sur le même registre alors on renvoie data
	QA <= Data when addW = A AND W = '1' else
			registr(to_integer(unsigned(A))); --when W = '0';
	QB <= Data when addW = B AND W = '1' else
			registr(to_integer(unsigned(B))); -- when W = '0';


--On considère que le reset et l'écriture se feront synchrone avec l'horloge.
		process
		begin
		wait until CLK'event and CLK='1';
-- Le signal reset RST est actif à 0 : le contenu du banc de registres est alors initialisé à 0x00.
			if RST = '0' then
					registr <= (others => (others => '0'));
			else
-- Cette entrée est active à 1, pour une écriture. Lorsque l'écriture est activée, les données présentent sur l'entrée DATA sont copiées dans le registre d'adresse @W
				if W = '1' then
					registr(to_integer(unsigned(addW))) <= Data;
				end if;
			end if;
		
	end process;
	
	
end Behavioral;
