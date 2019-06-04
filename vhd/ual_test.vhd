--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   09:39:33 04/18/2019
-- Design Name:   
-- Module Name:   /home/pflorenc/proco/ual_test.vhd
-- Project Name:  proco
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
 
ENTITY ual_test IS
END ual_test;
 
ARCHITECTURE behavior OF ual_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT ual
    PORT(
         A : IN  std_logic_vector(31 downto 0);
         B : IN  std_logic_vector(31 downto 0);
         Op : IN  std_logic_vector(7 downto 0);
         S : OUT  std_logic_vector(31 downto 0);
         Flags : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(31 downto 0) := (others => '0');
   signal B : std_logic_vector(31 downto 0) := (others => '0');
   signal Op : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal S : std_logic_vector(31 downto 0);
   signal Flags : std_logic_vector(3 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   --constant <clock>_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: ual PORT MAP (
          A => A,
          B => B,
          Op => Op,
          S => S,
          Flags => Flags
        );

   -- Clock process definitions
   --<clock>_process :process
   --begin
	--	<clock> <= '0';
	--	wait for <clock>_period/2;
	--	<clock> <= '1';
	--	wait for <clock>_period/2;
   --end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	


		-- 1 + 1  
		A <= x"00000001";
		B <= x"00000001";
		OP <= x"02";
		
		-- 1 - 1
		wait for 50 ns;
		OP <= x"03";
		
		-- 1 x 1
		wait for 50 ns;
		OP <= x"04";
		
		
		-- Max +1 => Carry prends 1
		wait for 50 ns;
		A <= x"FFFFFFFF";
		B <= x"00000001";
		OP <= x"02";
		
		-- 0 - 1 => Sign prends 1
		wait for 50 ns;
		A <= x"00000000";
		B <= x"00000001";
		OP <= x"03";
		
		-- + MAX + 1 => Overflow
		wait for 50 ns;
		A <= x"7FFFFFFF";
		B <= x"00000001";
		OP <= x"02";
		
		wait for 50 ns;
		-- - MAX + -1 => overflow
		A <= x"F0000000";
		B <= x"80000001";
		
      -- insert stimulus here 

      wait;
   end process;

END;
