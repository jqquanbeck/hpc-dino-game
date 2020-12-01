from __future__ import absolute_import, division, print_function

import base64
import imageio
import IPython
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import PIL.Image
import pyvirtualdisplay

import tensorflow as tf

from tf_agents.agents.dqn import dqn_agent
from tf_agents.drivers import dynamic_step_driver
from tf_agents.environments import suite_gym
from tf_agents.environments import tf_py_environment
from tf_agents.eval import metric_utils
from tf_agents.metrics import tf_metrics
from tf_agents.networks import q_network
from tf_agents.policies import random_tf_policy
from tf_agents.replay_buffers import tf_uniform_replay_buffer
from tf_agents.trajectories import trajectory
from tf_agents.utils import common

from translator import *

class DinoPolicy(tf_policy.TFPolicy):
    def __init__(self):
        self._observation_spec = array_spec.BoundedArraySpec(
            shape   = (14,), 
            dtype   = np.int32, 
            minimum = [0,0,0,0,0,0,0,0,0,0,0,0,0,0], 
            maximum = [
                600,150,6,     # Enemy 1
                600,150,6,     # Enemy 2
                600,150,6,     # Enemy 3
                600,150,6,     # Enemy 4
                100,2147483647 # Dino Jump and Score
            ],
            name    = "observation"
        )
        self._action_spec = array_spec.BoundedArraySpec(
            shape   = (), 
            dtype   = np.int32, 
            minimum = 0, # [Jump, None, Duck] 
            maximum = 2, 
            name    = "action"
        )

        super(DinoPolicy, self).__init__(time_step_spec=time_step_spec,
                                        action_spec=action_spec)
    def _distribution(self, time_step):
        pass

    def _variables(self):
        return ()

    def _action(self, time_step, policy_state, seed):
        observation_sign = tf.cast(tf.sign(time_step.observation[0]), dtype=tf.int32)
        action = observation_sign + 1
        return policy_step.PolicyStep(action, policy_state)