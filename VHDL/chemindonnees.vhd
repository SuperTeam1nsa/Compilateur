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
	OP : out std_logic_vector(7 downto 0);
	A  : out std_logic_vector(7 downto 0);
	B  : out std_logic_vector(7 downto 0);
	C  : out std_logic_vector(7 downto 0));

end chemindonnees;

architecture Behavioral of chemindonnees is


begin


end Behavioral;