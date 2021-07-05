# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).

tests = [ 
    # These tests are written in mind with pull down mode on the buttons, thus
    # input is inversed.

    { # Test 1: Goes into mode1. (no button press for 10 iters)
    'description': 'PINA: 0x01 => PORTB: 0xC0',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 10 },
               ],
    'expected': [('PORTB',0xC0)],
    },
 
    { # Test 2: Goes into mode2 and holds button down.
    'description': 'PINA: 0x00 => PORTB: 0x2A',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 12 },
               ],
    'expected': [('PORTB',0x2A)],
    },
 
    { # Test 3: Release button, expect mode2 and mode2R flag
    'description': 'PINA: 0x01 => PORTB: 0x2A',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 12 },
               ],
    'expected': [('PORTB',0x2A)],
    },
 
    { # Test 4: Press and release button to get into mode1 and mode1R flag
    'description': 'PINA: 0x00, 0x01 => PORTB: 0xC0',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 12 },
               {'inputs': [('PINA',0x00)], 'iterations': 10}],
    'expected': [('PORTB',0xC0)],
    },


]

watch = ['PINA', 'main::state', 'main::flag', 'main::tmpB', 'PORTB']
