--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   19:00:16 05/21/2020
-- Design Name:   
-- Module Name:   /home/hsahraou/Bureau/4A/COMPILATEUR/Compilateur/Compilateur/VHDL/Processeur/Processeur/Test_UAL.vhd
-- Project Name:  Processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: ual
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Test_UAL IS
END Test_UAL;
 
ARCHITECTURE behavior OF Test_UAL IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT ual
    PORT(
         A : IN  std_logic_vector(7 downto 0);
         B : IN  std_logic_vector(7 downto 0);
         Ctrl_Alu : IN  std_logic_vector(2 downto 0);
         S : OUT  std_logic_vector(7 downto 0);
         N : OUT  std_logic;
         O : OUT  std_logic;
         Z : OUT  std_logic;
         C : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(7 downto 0) := (others => '0');
   signal B : std_logic_vector(7 downto 0) := (others => '0');
   signal Ctrl_Alu : std_logic_vector(2 downto 0) := (others => '0');

 	--Outputs
   signal S : std_logic_vector(7 downto 0);
   signal N : std_logic;
   signal O : std_logic;
   signal Z : std_logic;
   signal C : std_logic;
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   constant clk_period : time := 10 ns;
	signal clk : std_logic;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: ual PORT MAP (
          A => A,
          B => B,
          Ctrl_Alu => Ctrl_Alu,
          S => S,
          N => N,
          O => O,
          Z => Z,
          C => C
        );

    -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin
		wait for 100 ns;

		A <= x"01";
		B <= x"01";
		Ctrl_Alu <= "001"; -- on veut 10 => rien du tout
		
		wait for 100 ns;
		
		A <= x"64"; -- 100
		B <= x"38"; -- 56
		Ctrl_Alu <= "001"; -- add
		-- on veut 156= x9C => carry et negatif
		
		wait for 100 ns;
		
		A <= x"64"; -- 100
		B <= x"38"; -- 56
		Ctrl_Alu <= "011"; -- soustraction
		-- on veut 44= x2C => rien du tout
		
		wait for 100 ns;
		
		A <= x"38"; -- 56
		B <= x"64"; -- 100
		Ctrl_Alu <= "011"; -- soustraction
		-- on veut -44= 172= xAC => negatif
		
		wait for 100 ns;
		
		A <= x"FF"; -- 255
		B <= x"02"; -- 2
		Ctrl_Alu <= "010"; -- multiplication
		-- on veut 510= x1FE => overflow, carry et negative
		
      wait for clk_period*12;
   end process;

END;
