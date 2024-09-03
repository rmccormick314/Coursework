# <-- BEGIN IMPORTS / HEADERS -->
import os
import urllib
import urllib.request
import pandas as pd
import numpy as np
import plotnine as p9
from plotnine import ggplot, geom_tile
import warnings
# <-- END IMPORTS / HEADERS -->

# <-- BEGIN INITIALIZATION -->
# FILE VARIABLES
download_directory = "."
file = "zip.test.gz"
url = "https://github.com/tdhock/cs570-spring-2022/raw/master/data/zip.test.gz"
file_path = os.path.join(download_directory, file)
# CONSTANT VARIABLES
NUM_PIXELS = 16  # 16 pixels per side of image
IMAGE_SIZE = 256 # 256 pixels total
NUM_IMAGES = 1000   # 9 images in a grid to be produced as final product
# <-- END INITIALIZATION -->

# <-- BEGIN FUNCTIONS -->
# FUNCTION: MAIN
#   Description  : Main driver for Assignment One
#   Inputs       : None
#   Outputs      : PlotNine graphs saved to program directory
#   Dependencies : build_image_df_from_dataframe
def main():
    # Display the title
    print("\nCS 499: Homework 1 Program Start")
    print("================================\n")

    # Suppress annoying plotnine warnings
    warnings.filterwarnings('ignore')

    # Check for data file. If not found, download
    if not os.path.isfile(file_path):
        try:
            print("Getting file: " + str(file) + "...\n")
            urllib.request.urlretrieve(url, file_path)
            print("File downloaded.\n")
        except(error):
            print(error)
    else:
        print("File: " + str(file) + " is already downloaded.\n")

    # Open the data file and assign to dataframe
    input_dataframe = pd.read_csv(file, header=None, sep=" ")

    # Print dataframe shape
    print("Data shape: " + str(input_dataframe.shape) + " [Unmodified]\n")

    # Drop index and print new size
    input_dataframe_no_index = input_dataframe.iloc[: , 1:]
    print("Data shape: " + str(input_dataframe_no_index.shape) + " [No Index]\n")

    # Convert dataframe to np array, print size
    input_data_array = input_dataframe.to_numpy()
    input_data_array_no_index = input_dataframe_no_index.to_numpy()
    print("Data shape: " + str(input_data_array_no_index.shape)
            + " [np Array, No Index]\n")

    # Print first row of data_array
    print("First row of Data: " + str(input_data_array[0]) + "\n")

    # Create a single image dataframe
    buffer_frame = build_image_df_from_dataframe(0, input_dataframe)

    # Turn single image dataframe into visual chart
    single_plot = (p9.ggplot(buffer_frame,
                             p9.aes(x='col', y='row', fill='intensity'))
                   + p9.geom_tile(color='black', size=0.5)
                   + p9.scale_fill_cmap('bone')
                   + p9.facet_wrap('uid')
                   + p9.theme(aspect_ratio=1))

    # Save single digit plot
    single_plot.save(filename = 'CS499_A1_SingleDigit.png')

    # Print confirmation of file save
    print("\nSaved plot: CS499_A1_SingleDigit.png")

    # Initialize the dataframe we will use to hold our multiple image frames
    multi_frames = pd.DataFrame()

    # Loop across a given range, building a dataframe for each image, and
    # concatenating it to a master image
    for index in range(NUM_IMAGES):
        buffer_frame = build_image_df_from_dataframe(index, input_dataframe)
        multi_frames = pd.concat([multi_frames, buffer_frame])

    # Generate the plot of all the images
    multi_plot = (p9.ggplot(multi_frames,
                            p9.aes(x='col', y='row', fill='intensity'))
            + p9.geom_tile(color='black', size=0.5)
            + p9.scale_fill_cmap('bone')
            + p9.facet_wrap('uid', labeller='both')
            + p9.theme(aspect_ratio=1))

    # Save multiple digits plot
    multi_plot.save(filename = 'CS499_A1_MultipleDigits.png')

    # Print confirmation of file save
    print("\nSaved plot: CS499_A1_MultipleDigits.png")

    # Display end of program
    print("\nCS 499: Homework 1 Program End")
    print("==============================")

# FUNCTION : BUILD_IMAGE_DF_FROM_DATAFRAME
#   Description: Builds data from a single data entry into a dataframe
#   Inputs:
#       - index     : index of input dataframe entry to convert
#       - dataframe : master dataframe of image data
#   Outputs:
#       - final_dataframe : completed dataframe for one image
def build_image_df_from_dataframe(index, input_dataframe):
    # Get a data entry at the given index of a given dataframe,
    # form it into a np array
    input_data_array = np.resize(((input_dataframe.iloc[index]).to_numpy()),
                                  (IMAGE_SIZE+1))

    # Get the numeric label of the data entry
    label_num = int(input_data_array[0])
    # Remove the label so we only have data
    input_data_array = input_data_array[1:]

    # Build dictionary which will become our dataframe
    data_dictionary = {
        # Columns go 1, 2, 3, ..., 1, 2, 3, ...
        'col' : np.resize(np.arange(NUM_PIXELS), IMAGE_SIZE),
        # Rows go 1, 1, 1, ..., 2, 2, 2, ...
        'row' : -np.repeat(np.arange(NUM_PIXELS), NUM_PIXELS),
        # Intensity data is unaltered
        'intensity' : input_data_array,
        # Unique ID (UID) is the entry number and label
        'uid' : np.repeat("Entry No. " + str(index) + " : #" + str(label_num),
                          IMAGE_SIZE)
    }

    # Build final dataframe
    final_dataframe = pd.DataFrame.from_dict(data_dictionary)

    # Show output to confirm dataframe was created, confirm size
    print("\nCompleted Dataframe: No. " + str(index) + " | #" + str(label_num))
    print(final_dataframe.shape)

    return(final_dataframe)
# <-- END FUNCTIONS -->

# Launch main
if __name__ == "__main__":
    main()
