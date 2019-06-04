--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   13:31:19 05/10/2019
-- Design Name:   
-- Module Name:   /home/pflorenc/proco/test_reg.vhd
-- Project Name:  proco
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: registers_bank
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
 
ENTITY test_reg IS
END test_reg;
 
ARCHITECTURE behavior OF test_reg IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT registers_bank
    PORT(
         clk : IN  std_logic;
         en : IN  std_logic;
         rst : IN  std_logic;
         w : IN  std_logic;
         reg1 : IN  std_logic_vector(7 downto 0);
         reg2 : IN  std_logic_vector(7 downto 0);
         reg1_out : OUT  std_logic_vector(31 downto 0);
         reg2_out : OUT  std_logic_vector(31 downto 0);
         regw : IN  std_logic_vector(7 downto 0);
         data_in : IN  std_logic_vector(31 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal en : std_logic := '0';
   signal rst : std_logic := '0';
   signal w : std_logic := '0';
   signal reg1 : std_logic_vector(7 downto 0) := (others => '0');
   signal reg2 : std_logic_vector(7 downto 0) := (others => '0');
   signal regw : std_logic_vector(7 downto 0) := (others => '0');
   signal data_in : std_logic_vector(31 downto 0) := (others => '0');

 	--Outputs
   signal reg1_out : std_logic_vector(31 downto 0);
   signal reg2_out : std_logic_vector(31 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: registers_bank PORT MAP (
          clk => clk,
          en => en,
          rst => rst,
          w => w,
          reg1 => reg1,
          reg2 => reg2,
          reg1_out => reg1_out,
          reg2_out => reg2_out,
          regw => regw,
          data_in => data_in
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
      -- hold reset state for 100 ns.
      wait for 100 ns;	
		en <= '1';
		rst <= '0';
		data_in <= x"AAAAAAAA";
		reg1 <= X"02";
		reg2 <= X"02";
		w <= '1';
		regw <= x"02";
		
		
      wait for clk_period*3;
		w <= '1';
		regw <= x"01";
		data_in <= x"BBBBBBBB";
		reg1 <= X"01";
		wait for clk_period*3;
		regw<= x"00";
		

      -- insert stimulus here 

      wait;
   end process;

END;
